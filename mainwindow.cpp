#include "mainwindow.h"
#include "buchungbearbeiten.h"
#include "neuersparplan.h"
#include "sparplaeneanschauen.h"
#include "sparplanbearbeiten.h"
#include "ui_mainwindow.h"
#include "neuebuchung.h"
#include "buchungenanschauen.h"
#include "profil.h"
#include "neuerbarchart.h"
#include "neuerpiechart.h"
#include<QMessageBox>

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myProfil = new Profil("Mustermann","EUR (€)");
    ui->BenutzerName->setText(QString::fromStdString(myProfil->getName()));
    ui->radioButtonJaehrlich->setChecked(true);
    connect(ui->pushButtonNeueBuchung,&QPushButton::clicked,this,&MainWindow::neueBuchung);
    connect(ui->pushButtonBuchungAnschauen,&QPushButton::clicked,this,&MainWindow::buchungAnschauen);
    connect(ui->pushButtonProfil,&QPushButton::clicked,this,&MainWindow::ProfilAnzeigen);
    connect(ui->pushButtonBuchungBearbeiten,&QPushButton::clicked,this,&MainWindow::buchungBearbeiten);
    connect(ui->pushButtonNeueSparplan, &QPushButton::clicked, this, &MainWindow::neuerSparplan);
    connect(ui->pushButtonSparplanBearbeiten, &QPushButton::clicked, this, &MainWindow::sparplanBearbeiten);
    connect(ui->pushButtonSparplaeneAnschauen, &QPushButton::clicked, this, &MainWindow::sparplaeneAnschauen);


    connect(ui->radioButtonTaeglich,&QPushButton::clicked,this,&MainWindow::Piecharttaeglich);
    connect(ui->radioButtonMonatlich,&QPushButton::clicked,this,&MainWindow::Piechartmonatlich);
    connect(ui->radioButtonJaehrlich,&QPushButton::clicked,this,&MainWindow::Piechartjaehrlich);


    //addBeispielBuchung();
    //load();

    getExchangeRates(apiKey);
    Barchartbauen();
    createPiechart();
}

MainWindow::~MainWindow()
{
    save();

    for(auto &a: einnahmen){
        delete a;
        a = nullptr;
    }
    for(auto &a: ausgaben){
        delete a;
        a = nullptr;
    }
    for(auto &a: rechnungen){
        delete a;
        a = nullptr;
    }

    delete myProfil;
    myProfil = nullptr;

    for(auto &a: sparplaene){
        delete a;
        a = nullptr;
    }

    delete myPiechart;
    myPiechart = nullptr;

    delete myBarchart;
    myBarchart = nullptr;

    delete myChartPie;
    myChartPie = nullptr;

    delete myChartBar;
    myChartBar = nullptr;
    delete ui;
}

void MainWindow::addBarchartDetails(){
    myChartBar = myBarchart->getR();
    myChartBar->setStyleSheet("background-color: rgb(132, 66, 99); color: white;");
    ui->Barchart_frame->setStyleSheet("background-color: rgb(132, 66, 99); color: white;");
    myChartBar->setRenderHints(QPainter::Antialiasing);
    ui->Barchart_frame->layout()->addWidget(myChartBar);
}

void MainWindow::Barchartbauen()
{
    myBarchart = new meinBarchart(einnahmen,ausgaben, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    addBarchartDetails();
}

void MainWindow::updateBarchart(){
    ui->Barchart_frame->layout()->removeWidget(myChartBar);
    myBarchart->update(einnahmen,ausgaben, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    addBarchartDetails();
}

void MainWindow::Piecharttaeglich()
{
    QDate currentDate = QDate::currentDate();
    vector<Ausgabe*> filteredObjects;
    for (const auto &ausgabe : ausgaben) {
        if (ausgabe->getDatum()== currentDate) {
            filteredObjects.push_back(ausgabe);
        }}
    ui->Piechart_frame->layout()->removeWidget(myChartPie);
    if(filteredObjects.empty()){
        Ausgabe* ausgabe =  new Ausgabe( 0.0, QDate::currentDate(), false,"", "Keine Ausgaben");
        filteredObjects.push_back(ausgabe);
    }
    myPiechart->updatePiechart(filteredObjects, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    showPiechartDesign();

}
void MainWindow::Piechartmonatlich()
{
    QDate currentDate = QDate::currentDate();
    vector<Ausgabe*> filteredObjects;
    for (const auto &ausgabe : ausgaben) {

        if (ausgabe->getDatum().month() == currentDate.month() && ausgabe->getDatum().year() == currentDate.year()) {
            filteredObjects.push_back(ausgabe);
        }}
    ui->Piechart_frame->layout()->removeWidget(myChartPie);
    if(filteredObjects.empty()){
        Ausgabe* ausgabe =  new Ausgabe( 0.0, QDate::currentDate(), false,"", "Keine Ausgaben");
        filteredObjects.push_back(ausgabe);
    }
    myPiechart->updatePiechart(filteredObjects, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    showPiechartDesign();
}

void MainWindow::showPiechartDesign(){
    myChartPie = myPiechart->getR();
    myChartPie->resize(410, 350);
    myChartPie->setAlignment(Qt::AlignLeft);
    ui->Piechart_frame->layout()->addWidget(myChartPie);
}

void MainWindow::Piechartjaehrlich()
{
    QDate currentDate = QDate::currentDate();
    vector<Ausgabe*> filteredObjects;
    for (const auto &ausgabe : ausgaben) {
        if (ausgabe->getDatum().year() == currentDate.year()) {
            filteredObjects.push_back(ausgabe);
        }
    }
    ui->Piechart_frame->layout()->removeWidget(myChartPie);
    if(filteredObjects.empty()){
        Ausgabe* ausgabe =  new Ausgabe( 0.0, QDate::currentDate(), false,"", "Keine Ausgaben");
        filteredObjects.push_back(ausgabe);
    }
    myPiechart->updatePiechart(filteredObjects, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    showPiechartDesign();
}

void MainWindow::createPiechart()
{
    vector<Ausgabe*> filteredObjects;
    for (const auto &ausgabe : ausgaben) {
        if (ausgabe->getDatum().year() == QDate::currentDate().year()) {
            filteredObjects.push_back(ausgabe);
        }}
    ui->Piechart_frame->layout()->removeWidget(myChartPie);
    if(filteredObjects.empty()){
        Ausgabe* ausgabe =  new Ausgabe( 0.0, QDate::currentDate(), false,"", "Keine Ausgaben");
        filteredObjects.push_back(ausgabe);
    }
    myPiechart = new meinPiechart(filteredObjects, myProfil->getWaehrung(), getEuro(), getYen(), getDollar());
    showPiechartDesign();
}
void MainWindow::setMyPiechart(meinPiechart *newMyPiechart)
{
    myPiechart = newMyPiechart;
}

void MainWindow::neueBuchung(){
    NeueBuchung* buchung = new NeueBuchung(this);
    buchung->show();
}

void MainWindow::buchungAnschauen(){
    BuchungenAnschauen* anschauen = new BuchungenAnschauen(this,einnahmen,ausgaben,rechnungen);
    anschauen->show();
}

void MainWindow::ProfilAnzeigen(){
    Profil* profil = new Profil(this);
    profil->show();

}

void MainWindow::buchungBearbeiten(){
    BuchungBearbeiten* bearbeiten = new BuchungBearbeiten(this);
    bearbeiten->show();
}

void MainWindow::neuerSparplan(){
    NeuerSparplan* sparplan = new NeuerSparplan(this);
    sparplan->show();
}

void MainWindow::sparplanBearbeiten(){
    SparplanBearbeiten* sparplanBearbeiten = new SparplanBearbeiten(this);
    sparplanBearbeiten->show();
}

void MainWindow::sparplaeneAnschauen(){
    SparplaeneAnschauen* sparplaeneAnschauen = new SparplaeneAnschauen(this,sparplaene);
    sparplaeneAnschauen->show();
}


void MainWindow::einnahmeHinzufuegen(Einnahme* einnahme){
    einnahmen.push_back(einnahme);
}

void MainWindow::ausgabenHinzufuegen(Ausgabe* ausgabe){
    ausgaben.push_back(ausgabe);
}

void MainWindow::rechnungHinzufuegen(Rechnung* rechnung){
    rechnungen.push_back(rechnung);
}

void MainWindow::sparplanHinzufuegen(Sparplan* sparplan){
    sparplaene.push_back(sparplan);
}

int MainWindow::getIndex(int BNr){
    for(unsigned int i{};i<einnahmen.size();i++){
        if(einnahmen[i]->getBuchungNr()==BNr){
            return i;
        }
    }
    for(unsigned int i{};i<ausgaben.size();i++){
        if(ausgaben[i]->getBuchungNr()==BNr){
            return i;
        }
    }
    for(unsigned int i{};i<rechnungen.size();i++){
        if(rechnungen[i]->getBuchungNr()==BNr){
            return i;
        }
    }
    return -1;
}

void MainWindow::save(){
    ofstream file;
    file.open ("haushalstbuchSave.txt");
    if(!file.is_open()){
        QMessageBox::information(this,"Fehler","Fehler beim Speichern");
        return;
    }
    file<<*myProfil<<endl;

    file<<einnahmen.size()<<endl;
    for(Einnahme *e : einnahmen){
        file<<*e<<endl;
    }

    file<<ausgaben.size()<<endl;
    for(Ausgabe *a : ausgaben){
        file<<*a<<endl;
    }

    file<<sparplaene.size()<<endl;
    for(Sparplan *s : sparplaene){
        file<<*s<<endl;
    }

    file<<rechnungen.size()<<endl;
    for(Rechnung *r : rechnungen){
        file<<*r<<endl;
    }
    file.close();
}

void MainWindow::load(){
    ifstream file;
    file.open ("haushalstbuchSave.txt");
    if(!file.is_open()){
        QMessageBox::information(this,"Fehler","Fehler beim Laden");
        return;
    }
    myProfil = new Profil("", "");
    file>>*myProfil;

    einnahmen.clear();
    ausgaben.clear();
    sparplaene.clear();
    rechnungen.clear();

    int einnahmenSize;
    file>>einnahmenSize;
    for(int i{0}; i<einnahmenSize; i++){
        Einnahme *e = new Einnahme();
        file>>*e;
        einnahmen.push_back(e);
    }

    int ausgabenSize;
    file>>ausgabenSize;
    for(int i{0}; i<ausgabenSize; i++){
        Ausgabe *a = new Ausgabe();
        file>>*a;
        ausgaben.push_back(a);
    }

    int sparplaeneSize;
    file>>sparplaeneSize;
    for(int i{0}; i<sparplaeneSize; i++){
        Sparplan *s = new Sparplan();
        file>>*s;
        sparplaene.push_back(s);
    }

    int rechnungenSize;
    file>>rechnungenSize;
    for(int i{0}; i<rechnungenSize; i++){
        Rechnung *r = new Rechnung();
        file>>*r;
        rechnungen.push_back(r);
    }

    file.close();

}

void MainWindow::delAusgabe(int i){
    int index = getIndex(i);
    if(index != -1){
        try{
            Ausgabe* deleted = ausgaben.at(index);
            ausgaben.erase(ausgaben.begin()+index);
            delete deleted;
            QMessageBox::information(this,"Gelöscht","Ausgabe erfolgreich gelöscht");
        }catch(...){
            QMessageBox::information(this,"Fehler","Ausgabe nicht gelöscht");
        }
    }else{
        QMessageBox::information(this,"Fehler","BuchungNr falsch");
    }
}

void MainWindow::delEinnahme(int i){
    int index = getIndex(i);
    if(index != -1){
        try{
            Einnahme* deleted = einnahmen.at(index);
            einnahmen.erase(einnahmen.begin()+index);
            delete deleted;
            QMessageBox::information(this,"Gelöscht","Einnahme erfolgreich gelöscht");
        }catch(...){
            QMessageBox::information(this,"Fehler","Einnahme nicht gelöscht");
        }
    }else{
        QMessageBox::information(this,"Fehler","BuchungNr falsch");
    }
}

void MainWindow::delRechnung(int i){
    int index = getIndex(i);
    if(index != -1){
        try{
            Rechnung* deleted = rechnungen.at(index);
            rechnungen.erase(rechnungen.begin()+index);
            delete deleted;
            QMessageBox::information(this,"Gelöscht","Rechnung erfolgreich gelöscht");
        }
        catch(...){
            QMessageBox::information(this,"Fehler","Rechung nicht gelöscht");
        }
    }
    else{
        QMessageBox::information(this,"Fehler","BuchungNr falsch");
    }
}

int MainWindow::getSparplanIndex(int n){
    for(unsigned int i{};i<sparplaene.size();i++){
        if(sparplaene[i]->getSparplanNr() == n){
            return i;
        }
    }
    return -1;
}

void MainWindow::delSparplan(int n){
    int index = getSparplanIndex(n);
    if(index!=-1){
        Sparplan* deleted = sparplaene[index];
        sparplaene.erase(sparplaene.begin() + index);
        delete deleted;
        QMessageBox::information(this,"Gelöscht","Sparplan erfolgreich gelöscht");
    }
    else{
        QMessageBox::information(this,"Fehler","SparplanNr falsch");
    }
}

Buchung* MainWindow::getBuchung(int BNr){

    for(auto &a:einnahmen){
        if(a->getBuchungNr()==BNr){
            return a;
        }
    }
    for(auto &a:ausgaben){
        if(a->getBuchungNr()==BNr){
            return a;
        }
    }
    for(auto &a:rechnungen){
        if(a->getBuchungNr()==BNr){
            return a;
        }
    }
    return nullptr;
}

Sparplan* MainWindow::getSparplan(int SNr){
     for(auto &a: sparplaene){
        if(a->getSparplanNr()==SNr){
            return a;
        }
   }
   return nullptr;
}

Profil* MainWindow::getProfil(){
    return myProfil;
}

void MainWindow::refresh(){
    ui->BenutzerName->setText(QString::fromStdString(myProfil->getName()));
    updateBarchart();
    Piechartjaehrlich();
}

void MainWindow::getExchangeRates(const QString &apiKey) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://open.er-api.com/v6/latest"));

    // Fügen Sie den API-Schlüssel hinzu.
    request.setRawHeader("Authorization", apiKey.toUtf8());

    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
            QJsonObject rates = jsonResponse["rates"].toObject();

            setDollarToDollar(rates["USD"].toDouble());
            setDollarToYen(rates["JPY"].toDouble());
            setDollarToEuro(rates["EUR"].toDouble());
        }
        else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        QCoreApplication::quit();
    });

    QCoreApplication::exec();
}

double MainWindow::getYen() const
{
    return Yen;
}

double MainWindow::getDollar() const
{
    return Dollar;
}

double MainWindow::convertToUSD(double euroAmount) {

    const double usdExchangeRate = 1.0 / getEuro();
    return euroAmount * usdExchangeRate;
}

double MainWindow::convertToJPY(double euroAmount) {

    const double jpyExchangeRate = getYen();
    double usdAmount = convertToUSD(euroAmount);
    return usdAmount * jpyExchangeRate;
}

double MainWindow::convertToEurofromUSD(double usdAmount) {
    const double exchangeRate = getEuro();
    return usdAmount * exchangeRate;
}
double MainWindow::convertToEurofromJPY(double jpyAmount) {
    const double exchangeRate = getYen();
    double usdAmount = jpyAmount / exchangeRate;
    return convertToEurofromUSD(usdAmount);
}

double MainWindow::getEuro() const
{
    return Euro;
}

void MainWindow::setDollarToEuro(double newEuro)
{
    Euro = newEuro;
}

void MainWindow::setDollarToDollar(double newDollarToDollar)
{
    Dollar = newDollarToDollar;
}

void MainWindow::addBeispielBuchung(){
    Ausgabe* ausgabe1 = new Ausgabe(50.0, QDate(2023, 12, 8), false,"Lebensmittel",  "Einkauf im Supermarkt");
    Ausgabe* ausgabe2 = new Ausgabe(30.0, QDate(2023, 12, 7), true,"Transport",  "Taxifahrt zum Flughafen");
    Ausgabe* ausgabe3 = new Ausgabe( 10.0, QDate(2024, 12, 6), false,"Geschenke", "Geburtstagsgeschenk für Freund");
    Ausgabe* ausgabe4 = new Ausgabe( 10.0, QDate(2024, 12, 5),true,"Versicherungen",  "Monatliche Versicherungsprämie");
    Ausgabe* ausgabe5 = new Ausgabe( 25.0, QDate(2024, 12, 4), false, "Restaurants","Abendessen mit Familie");
    Ausgabe* ausgabe6 = new Ausgabe(50.0, QDate(2024, 12, 3), true,"UnvorhergeseheneAusgaben",  "Reparaturkosten für Auto");
    Ausgabe* ausgabe7 = new Ausgabe(175.0, QDate(2023, 12, 2), false,"Reisen",  "Hotel während Urlaubsreise");
    Ausgabe* ausgabe8 = new Ausgabe( 40.0, QDate(2023, 12, 1), true, "Hobbys","Bastelmaterialien für Hobbyprojekt");
    Ausgabe* ausgabe9 = new Ausgabe(90.0, QDate(2024, 1, 28), false,"Bildungsausgaben",  "Bücher für Studium");
    Ausgabe* ausgabe10 = new Ausgabe(25.0, QDate(2024, 2, 29), true,"Haushaltsbedarf",  "Reinigungsmittel für Zuhause");
    Ausgabe* ausgabe11 = new Ausgabe(200.0, QDate(2023, 3, 28), false,"Elektronik",  "Neues Smartphone");
    Ausgabe* ausgabe12 = new Ausgabe( 80.0, QDate(2024, 4, 27), true,"Gesundheit", "Arztbesuch und Medikamente");
    Ausgabe* ausgabe13 = new Ausgabe( 60.0, QDate(2023, 5, 26), false,"Freizeitaktivitäten", "Kinobesuch mit Freunden");
    Ausgabe* ausgabe14 = new Ausgabe( 120.0, QDate(2023, 6, 25), true,"Kleidung", "Einkauf neuer Winterkleidung");
    Ausgabe* ausgabe15 = new Ausgabe(40.0, QDate(2023, 7, 24), false,"Sport",  "Fitnessstudio-Mitgliedschaft");
    Ausgabe* ausgabe16 = new Ausgabe(150.0, QDate(2023, 8, 23), true,"Technologie",  "Tablet für berufliche Nutzung");
    Ausgabe* ausgabe17 = new Ausgabe( 12.0, QDate(2023, 12, 12), false,"Haus", "Haus");
    Ausgabe* ausgabe18 = new Ausgabe( 25.0, QDate(2023, 12, 12), false,"Hausreparaturen", "Essen");
    Ausgabe* ausgabe19 = new Ausgabe( 50.0, QDate(2023, 12, 12), false,"Fitnessstudio", "Fitnessstudio");
    Ausgabe* ausgabe20 = new Ausgabe( 8.0, QDate(2024, 12, 12), false,"Hausreparaturen", "Hygieneprodukte");
    Ausgabe* ausgabe21 = new Ausgabe( 20.0, QDate(2023, 12, 12), false,"Hausreparaturen", "Haustier");

    ausgaben.push_back(ausgabe1);
    ausgaben.push_back(ausgabe2);
    ausgaben.push_back(ausgabe3);
    ausgaben.push_back(ausgabe4);
    ausgaben.push_back(ausgabe5);
    ausgaben.push_back(ausgabe6);
    ausgaben.push_back(ausgabe7);
    ausgaben.push_back(ausgabe8);
    ausgaben.push_back(ausgabe9);
    ausgaben.push_back(ausgabe10);
    ausgaben.push_back(ausgabe11);
    ausgaben.push_back(ausgabe12);
    ausgaben.push_back(ausgabe13);
    ausgaben.push_back(ausgabe14);
    ausgaben.push_back(ausgabe15);
    ausgaben.push_back(ausgabe16);
    ausgaben.push_back(ausgabe17);
    ausgaben.push_back(ausgabe18);
    ausgaben.push_back(ausgabe19);
    ausgaben.push_back(ausgabe20);
    ausgaben.push_back(ausgabe21);

    Einnahme* einnahme1 = new Einnahme(10.5, QDate(2024, 6, 8), true, "Neue Schuhe", "einmalig");
    einnahmen.push_back(einnahme1);
    Einnahme* einnahme2 = new Einnahme(500.0, QDate(2024, 1, 10), true, "Bonus", "zusätzlich");
    einnahmen.push_back(einnahme2);
    Einnahme* einnahme3 = new Einnahme(900.0, QDate(2024, 3, 1), true, "Miete", "monatlich");
    einnahmen.push_back(einnahme3);
    Einnahme* einnahme4 = new Einnahme(400.0, QDate(2024, 7, 5), true, "Verkauf", "einmalig");
    einnahmen.push_back(einnahme4);
    Einnahme* einnahme5 = new Einnahme(200.0, QDate(2024, 12, 5), true, "Verkauf", "einmalig");
    einnahmen.push_back(einnahme5);
    Einnahme* einnahme6 = new Einnahme(450.0, QDate(2024, 4, 5), true, "Verkauf", "einmalig");
    einnahmen.push_back(einnahme6);
    Einnahme* einnahme7 = new Einnahme(200.0, QDate(2024, 2, 5), true, "Verkauf", "einmalig");
    einnahmen.push_back(einnahme7);
    Einnahme* einnahme8 = new Einnahme(300.0, QDate(2024, 5, 5), true, "Verkauf", "einmalig");
    einnahmen.push_back(einnahme8);
}

void MainWindow::setDollarToYen(double newDollarToYen)
{
    Yen = newDollarToYen;
}
