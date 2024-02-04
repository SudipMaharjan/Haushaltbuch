#include "neuerpiechart.h"
#include "ausgabe.h"
#include <string>




vector<Ausgabe*> meinPiechart::getAusgabenListe() const
{
    return ausgabenListe;
}

void meinPiechart::setAusgabenListe(const vector<Ausgabe*> &newAusgabenListe)
{
    ausgabenListe = newAusgabenListe;
}

double meinPiechart::getEUR() const
{
    return EUR;
}

double meinPiechart::getYEN() const
{
    return YEN;
}

double meinPiechart::getUSD() const
{
    return USD;
}

int meinPiechart::getSumme() const
{
    return Summe;
}

void meinPiechart::setSumme(int newSumme)
{
    Summe = newSumme;
}


meinPiechart::meinPiechart(vector<Ausgabe *> newAusgabenListe, string newWährung, double newEUR, double newYEN, double newUSD)
    : ausgabenListe(newAusgabenListe),Währung(newWährung),EUR(newEUR),YEN(newYEN),USD(newUSD)
{
    ch = new QChart();
    r = new QChartView();
    s = new QPieSeries();
    statusChange(ausgabenListe);
}

void meinPiechart::updatePiechart(vector<Ausgabe *> newAusgabenListe, string newWährung, double newEUR, double newYEN, double newUSD){
    Währung = newWährung;
    EUR = newEUR;
    YEN = newYEN;
    USD = newUSD;
    ch = new QChart();
    r = new QChartView();
    s = new QPieSeries();
    ausgabenListe = newAusgabenListe;
    statusChange(ausgabenListe);
}
double meinPiechart::convertToUSD(double euroAmount) {

    const double usdExchangeRate = 1 / getEUR();
    return euroAmount * usdExchangeRate;
}

double meinPiechart::convertToJPY(double euroAmount) {

    const double jpyExchangeRate = getYEN();
    double usdAmount = convertToUSD(euroAmount);
    return usdAmount * jpyExchangeRate;
}


string meinPiechart::getWährung() const
{
    return Währung;
}

void meinPiechart::setWährung(const string &newWährung)
{
    Währung = newWährung;
}


QChartView *meinPiechart::getR() const
{
    return r;
}

meinPiechart::~meinPiechart(){
    for(auto&a: ausgabenListe){
        delete a;
        a = nullptr;
    }
        delete s; s= nullptr;
        delete ch; ch= nullptr;
        delete r; r= nullptr;

}

void meinPiechart::statusChange( vector<Ausgabe*> ausgabenListe) {
    setSumme(0);
    map<string, double> kategorieSummen;

    for (const auto& ausgabe : ausgabenListe) {
        string kategorie = ausgabe->getKategorie().toStdString();
        double betrag = ausgabe->getBetrag();
        kategorieSummen[kategorie] += betrag;
    }

    // Convert the map to a vector of pairs
    vector<pair<string, double>> vecKategorien(kategorieSummen.begin(), kategorieSummen.end());

    // Sort by value in descending order
    sort(vecKategorien.begin(), vecKategorien.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (vecKategorien.size() >= 4) {
        double summeTopVier = accumulate(vecKategorien.begin(), vecKategorien.begin() + 4, 0.0,
                                [](double sum, const auto& pair) { return sum + pair.second; });

        double summeAllerKategorien = accumulate(vecKategorien.begin(), vecKategorien.end(), 0.0,
                                       [](double sum, const auto& pair) { return sum + pair.second; });

        for (int i = 0; i < 4; ++i) {
            addSlice(vecKategorien[i].first, vecKategorien[i].second);
        }

        double betragSonstige = summeAllerKategorien - summeTopVier;
        setSumme(summeAllerKategorien);
        convertAndAddSlice("Sonstige", betragSonstige);
    }
    else {
        for (const auto& pair : vecKategorien) {
            convertAndAddSlice(pair.first, pair.second);
        }
    }

    editDetails();
}

void meinPiechart::addSlice(const string& kategorie, double betrag) {
    QFont chartFontlabel("Segoe UI", 7, 450, true);
    QPieSlice* slice = s->append(QString::fromStdString(kategorie), betrag);
    slice->setLabelFont(chartFontlabel);
    slice->setLabelColor(Qt::white);
}

void meinPiechart::convertAndAddSlice(const string& kategorie, double betrag) {
    if (getWährung() == "USD ($)") {
        betrag = convertToUSD(betrag);
    }
    else if (getWährung() == "YEN (¥)") {
        betrag = convertToJPY(betrag);
    }
    setSumme(getSumme() + betrag);
    addSlice(kategorie, betrag);
}


void meinPiechart::editDetails() {
    QFont chartFont("Segoe UI", 10, 450, true);
    s->setLabelsVisible(true);
    ch->addSeries(s);
    ch->setTitle("Ausgaben" "  " "Summe: " + QString::number(getSumme()) + "  " + QString::fromStdString(Währung));
    ch->legend()->hide();
    ch->legend()->setColor(Qt::white);
    ch->setTitleBrush(QBrush(QColor(255, 255, 255)));
    ch->setBackgroundBrush(QBrush(QColor(132, 66, 99)));
    ch->setFont(chartFont);
    ch->setTitleFont(chartFont);
    ch->legend()->setFont(chartFont);
    r->setStyleSheet("background-color: rgb(132, 66, 99); color: white;");
    r->setChart(ch);
}
