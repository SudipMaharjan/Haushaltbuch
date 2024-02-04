#include "neuerbarchart.h"


string meinBarchart::getWährung() const
{
return Währung;
}

void meinBarchart::setWährung(const string &newWährung)
{
Währung = newWährung;
}

double meinBarchart::convertToUSD(double euroAmount) {

    const double usdExchangeRate = 1 / EUR;
    return euroAmount * usdExchangeRate;
}

double meinBarchart::convertToJPY(double euroAmount) {

    const double jpyExchangeRate = getYEN();
    double usdAmount = convertToUSD(euroAmount);
    return usdAmount * jpyExchangeRate;
}
double meinBarchart::getYEN() const
{
    return YEN;
}

double meinBarchart::getEUR() const
{
    return EUR;
}

double meinBarchart::getUSD() const
{
    return USD;
}

meinBarchart::meinBarchart(vector<Einnahme*> einnahmenListe, vector<Ausgabe*> ausgabenListe, string newWährung, double Euro, double Yen, double Dollar)
    : Währung(newWährung), EUR(Euro), YEN(Yen), USD(Dollar)
{
    addNewData();
    vector<int> gesamtEinnahmenProMonat(12, 0); // Ein Vektor, um die Gesamteinnahmen für jeden Monat zu speichern
    vector<int> gesamtAusgabenProMonat(12, 0); // Ein Vektor, um die Gesamtausgaben für jeden Monat zu speichern
    vector<int> sparRateProMonat(12, 0);
    double maximalEinnahmen = 0.0;
    double maximalAusgaben = 0.0;
    double Maximalwert = 0.0;

    processEinnahmenListe(einnahmenListe, gesamtEinnahmenProMonat, maximalEinnahmen);
    processAusgabenListe(ausgabenListe, gesamtAusgabenProMonat, maximalAusgaben);
    calculateSparRate(gesamtEinnahmenProMonat, gesamtAusgabenProMonat, sparRateProMonat,maximalEinnahmen, maximalAusgaben, Maximalwert);
    setupChart(Maximalwert);
}

void meinBarchart::processEinnahmenListe(vector<Einnahme*> einnahmenListe, vector<int> &gesamtEinnahmenProMonat, double& maximalEinnahmen){

    for (const auto& einnahme : einnahmenListe) {
        if(einnahme->getDatum().year() == QDate::currentDate().year()){
        int monat = einnahme->getDatum().month();
        int betrag = einnahme->getBetrag();
        if(getWährung() == "USD ($)"){
            betrag = convertToUSD(betrag);
        }
        else if(getWährung() == "YEN (¥)") {
            betrag = convertToJPY(betrag);
        }
        gesamtEinnahmenProMonat[monat - 1] += betrag;
        }        // Monate starten üblicherweise bei 1, daher Monatsindex - 1
    }
    e->setColor(QColor(66, 132, 99));

    for (int einnahmenMonat : gesamtEinnahmenProMonat) {
        *e << einnahmenMonat;
        if(einnahmenMonat >= maximalEinnahmen){
            maximalEinnahmen = einnahmenMonat;
        }
    }
}
void meinBarchart::processAusgabenListe(vector<Ausgabe*> ausgabenListe, vector<int>& gesamtAusgabenProMonat, double& maximalAusgaben){

        for (const auto& ausgabe : ausgabenListe) {
            if(ausgabe->getDatum().year() == QDate::currentDate().year()){
            int monat = ausgabe->getDatum().month();
            int betrag = ausgabe->getBetrag();
            if(getWährung() == "USD ($)"){
                betrag = convertToUSD(betrag);

            } else if(getWährung() == "YEN (¥)") {
                betrag = convertToJPY(betrag);
            }
            gesamtAusgabenProMonat[monat - 1] += betrag;
            }
        }
        a->setColor(QColor(180, 50, 50));
        for (int ausgabenMonat : gesamtAusgabenProMonat) {
            *a << ausgabenMonat;
            if( ausgabenMonat >= maximalAusgaben)maximalAusgaben = ausgabenMonat;
        }
}

void meinBarchart::calculateSparRate(vector<int> &gesamtEinnahmenProMonat, vector<int> &gesamtAusgabenProMonat, vector<int> &gesamtSparRateProMonat, double& maximalAusgaben, double& maximalEinnahmen, double& Maximalwert){

        for (int i = 0; i < 12; ++i) {
            gesamtSparRateProMonat[i] = gesamtEinnahmenProMonat[i] - gesamtAusgabenProMonat[i];
        }
        s->setColor(QColor(66, 99, 132));

        for (int sparrateMonat : gesamtSparRateProMonat) {
            *s << sparrateMonat;
        }

        if(maximalAusgaben >= maximalEinnahmen){
            Maximalwert = maximalAusgaben;
        }
        else{
            Maximalwert = maximalEinnahmen;
        }
}

void meinBarchart::setupChart(double& Maximalwert){
        series->append(e);
        series->append(a);
        series->append(s);

        c->addSeries(series);
        c->setTitle("monatlicher Überblick " + QString::number(QDate::currentDate().year()));
        c->setTitleBrush(QBrush(QColor(255, 255, 255)));
        c->setAnimationOptions(QChart::SeriesAnimations);
        c->setBackgroundBrush(QBrush(QColor(132, 66, 99)));
        c->legend()->setAlignment(Qt::AlignBottom);

        QStringList categories;
        categories << "Jan" << "Feb" << "Mär" << "Apr" << "Mai" << "Jun" << "Jul" << "Aug" << "Sep" << "Okt" << "Nov" << "Dez";

        axisY->setTitleText("Betrag in " + QString::fromStdString(this->Währung));
        axisY->setTitleBrush(QBrush(QColor(255, 255, 255)));
        axisY->setLinePenColor(QColor(255, 255, 255)); // Farbe der Linien der Y-Achse
        axisY->setLabelsColor(QColor(255, 255, 255)); // Farbe der Y-Achsen-Beschriftung
        axisY->setTickAnchor(0.0);
        axisY->setRange(-(Maximalwert+1), Maximalwert+1);
        c->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        series->attachAxis(axisX);
        axisX->setLinePenColor(QColor(255, 255, 255));
        axisX->setLabelsColor(QColor(255, 255, 255));
        axisX->append(categories);
        axisX->setTitleText("Monate");
        axisX->setTitleBrush(QBrush(QColor(255, 255, 255)));
        c->addAxis(axisX, Qt::AlignBottom);
        c->legend()->setLabelBrush(QBrush(QColor(255, 255, 255)));
        series->setVisible(true);
        QFont chartFontueberschrift("Segoe UI", 10, 450, true);
        QFont chartFont("Segoe UI", 8, 450, true);
        c->setTitleFont(chartFontueberschrift);
        axisY->setTitleFont(chartFont);
        axisX->setTitleFont(chartFont);
        axisY->setLabelsFont(chartFont);
        axisX->setLabelsFont(chartFont);
        c->legend()->setFont(chartFont);
        r->resize(1250, 300);
}

void meinBarchart::addNewData(){
    c = new QChart();
    series = new QBarSeries();
    e = new QBarSet("Einnahmen");
    a = new QBarSet("Ausgaben");
    s = new QBarSet("Sparrate");
    axisY = new QValueAxis();
    axisX = new QBarCategoryAxis();
    r = new QChartView(c);
}

void meinBarchart::update(vector<Einnahme*> einnahmenListe,vector<Ausgabe*> ausgabenListe, string newWährung,double newEUR, double newYEN, double newUSD){
    Währung = newWährung;
    EUR = newEUR;
    YEN = newYEN;
    USD = newUSD;

    addNewData();

    vector<int> gesamtEinnahmenProMonat(12, 0); // Ein Vektor, um die Gesamteinnahmen für jeden Monat zu speichern
    vector<int> gesamtAusgabenProMonat(12, 0); // Ein Vektor, um die Gesamtausgaben für jeden Monat zu speichern
    vector<int> sparRateProMonat(12, 0);
    double maximalEinnahmen = 0.0;
    double maximalAusgaben = 0.0;
    double Maximalwert = 0.0;

    processEinnahmenListe(einnahmenListe, gesamtEinnahmenProMonat, maximalEinnahmen);
    processAusgabenListe(ausgabenListe, gesamtAusgabenProMonat, maximalAusgaben);
    calculateSparRate(gesamtEinnahmenProMonat, gesamtAusgabenProMonat, sparRateProMonat,maximalEinnahmen, maximalAusgaben, Maximalwert);
    setupChart(Maximalwert);
}


meinBarchart::~meinBarchart(){
    delete c; c= nullptr;
    delete r; r= nullptr;
    delete e; e= nullptr;
    delete a; a= nullptr;
    delete s; s= nullptr;
    delete series; series= nullptr;
    delete axisX; axisX= nullptr;
    delete axisY; axisY= nullptr;
}

QChartView *meinBarchart::getR() const
{
    return r;
}

void meinBarchart::setR(QChartView *newR)
{
    r = newR;
}
