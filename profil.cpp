#include "profil.h"
#include "mainwindow.h"
#include "ui_profil.h"
#include<QMessageBox>

Profil::Profil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profil)
{
    ui->setupUi(this);
    //setGespartes(421.22);    //beispiel Wert. nach 100 € erhöht sich das Level (56 = level 1, 156 = level 2 usw.)
    QDate now;
    now=now.currentDate();
    double gesp=0.0;
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
    for(unsigned int o=0;o<mainWindow->sparplaene.size();o++){
        if(mainWindow->sparplaene[o]->getZielDatum()<=now){
            gesp=gesp+mainWindow->sparplaene[o]->getZielBetrag();
        }
    }
    setGespartes(gesp);
    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&Profil::zurueck);
    connect(ui->pushButtonAenderungSpeicchern,&QPushButton::clicked,this,&Profil::anpassen);
    showDetails();
}

Profil::Profil(){

}

Profil::Profil(string name, string waehrung) : name{name}, waehrung{waehrung}
{

}

void Profil::addProfil(string n, string w){
    name = n;
    waehrung = w;
}

string Profil::getName() const
{
    return name;
}

void Profil::setName(const string &value)
{
    name = value;
}

double Profil::getGespartes() const
{
    return gespartes;
}

void Profil::setGespartes(double value)
{
    gespartes = value;
}

Profil::~Profil()
{
    delete ui;
}

void Profil::zurueck(){
    close();
}

void Profil::anpassen(){
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    string n = ui->name->text().toStdString();
    mainWindow->getProfil()->setName(n);

    string waehrung = ui->comboBox->currentText().toStdString();
    mainWindow->getProfil()->setWaehrung(waehrung);

    mainWindow->refresh();

    QMessageBox::information(this,"Angepasst","Änderungen gespeichert");
    showDetails();
    showLevel();
    close();
}

void Profil::showLevel(){
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    int progressBarValue = static_cast<int>(gespartes) % 100;
    ui->progressBar->setValue(progressBarValue);
    int level = static_cast<int>(gespartes) / 100 + 1;
    ui->level->setText(QString::number(level));

    QString levelupInfo;
    if(mainWindow->getProfil()->getWaehrung()== "EUR (€)"){
        levelupInfo = QString::number(100 - progressBarValue);
        levelupInfo += " € noch bis zum nächsten Level";
        ui->label_3->setText(levelupInfo);
    }
    else if(mainWindow->getProfil()->getWaehrung() == "YEN (¥)"){
        levelupInfo = QString::number(mainWindow->convertToJPY(100 - progressBarValue));
        levelupInfo += " ¥ noch bis zum nächsten Level";
        ui->label_3->setText(levelupInfo);
    }
    else if(mainWindow->getProfil()->getWaehrung() == "USD ($)"){
        levelupInfo = QString::number(mainWindow->convertToUSD(100 - progressBarValue));
        levelupInfo += " $ noch bis zum nächsten Level";
        ui->label_3->setText(levelupInfo);
    }
}

string Profil::getWaehrung() const
{
    return waehrung;
}

void Profil::setWaehrung(const string &newWaehrung)
{
    waehrung = newWaehrung;
}

void Profil::showDetails(){
    showLevel();

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    QString n = QString::fromStdString(mainWindow->getProfil()->getName());
    ui->name->setText(n);

    if(mainWindow->getProfil()->getWaehrung()== "EUR (€)"){
        ui->gespart->setText(QString::number(gespartes) + " €");
    }
    else if(mainWindow->getProfil()->getWaehrung() == "YEN (¥)"){
        double value = mainWindow->convertToJPY(gespartes);
        ui->gespart->setText(QString::number(value) + " ¥");
    }
    else if(mainWindow->getProfil()->getWaehrung() == "USD ($)"){
        double value = mainWindow->convertToUSD(gespartes);
        ui->gespart->setText(QString::number(value) + " $");
    }

    QStringList items = {"USD ($)", "YEN (¥)", "EUR (€)"};
    ui->comboBox->addItems(items);
}

ostream& operator<<(ostream& os, const Profil& p){
    os << string(to_string(p.getGespartes()))<<endl;
    os << p.getWaehrung()<<endl;
    os << p.getName();
    return os;
}

istream& operator>>(istream& is, Profil& p){
    string output;
    //gespartes
    is>>output;
    p.setGespartes(std::stod(output));

    char w[256];
    is.getline (w, 256);
    cout<<w<<endl;
    //Waehrung
    char waehrung[256];
    is.getline (waehrung, 256);
    p.setWaehrung(waehrung);
    //Name
    char name[256];
    is.getline (name, 256);
    p.setName(name);

    return is;
}
