#include "neuebuchung.h"
#include "mainwindow.h"
#include "ui_neuebuchung.h"
#include <QMessageBox>

NeueBuchung::NeueBuchung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NeueBuchung)
{
    ui->setupUi(this);
    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&NeueBuchung::zurueck);
    connect(ui->pushButtonBestaetigen,&QPushButton::clicked,this,&NeueBuchung::bestaetigen);
    connect(ui->radioButtonEinnahme, &QRadioButton::toggled, this, &NeueBuchung::populateComboBox);
    connect(ui->radioButtonAusgabe, &QRadioButton::toggled, this, &NeueBuchung::populateComboBox);
    connect(ui->radioButtonRechnung, &QRadioButton::toggled, this, &NeueBuchung::populateComboBox);
    ui->dateEditDatum->setDate(QDate::currentDate());
    ui->dateEditFaelligkeitsdatum->setDate(QDate::currentDate());
    ui->radioButtonEinnahme->setChecked(true);
    ui->radioButtonJa->setChecked(true);
    QStringList items = {   "€", "$", "¥"} ;
    ui->comboBox_2->addItems(items);
}

NeueBuchung::~NeueBuchung()
{
    delete ui;
}

void NeueBuchung::populateComboBox() {
    ui->comboBox->clear();
    if (ui->radioButtonEinnahme->isChecked()) {
        QStringList items = {"Regel", "Einmalig", "Geliehen"};
        ui->comboBox->addItems(items);
    }

    else if (ui->radioButtonAusgabe->isChecked()) {
        QStringList items = {   "MieteHypothek", "Lebensmittel", "Haushaltsbedarf", "Versorgungsunternehmen", "Transport", "Kleidung", "SchoenheitPflege",
                             "Gesundheitswesen","Restaurants", "Unterhaltung", "Reisen", "Hobbys", "Bankgebuehren", "Kreditkartenzahlungen", "Investitionen",
                             "Bildungsausgaben", "Geschenke", "Spenden", "Versicherungen", "UnvorhergeseheneAusgaben","Sparen", "Sonstige"} ;
        ui->comboBox->addItems(items);
    }

    else if (ui->radioButtonRechnung->isChecked()) {
        QStringList items = {   "MieteHypothek", "Lebensmittel", "Haushaltsbedarf", "Versorgungsunternehmen", "Transport", "Kleidung", "SchoenheitPflege",
                             "Gesundheitswesen","Restaurants", "Unterhaltung", "Reisen", "Hobbys", "Bankgebuehren", "Kreditkartenzahlungen", "Investitionen",
                             "Bildungsausgaben", "Geschenke", "Spenden", "Versicherungen", "UnvorhergeseheneAusgaben","Sparen", "Sonstige"} ;
        ui->comboBox->addItems(items);
    }

}

void NeueBuchung::zurueck(){
    close();
}

bool NeueBuchung::buchungUnvollstaendig(){
    QString betrag = ui->betrag->toPlainText();
    if(betrag == ""){
        return true;
    }
    return false;
}

void NeueBuchung::bestaetigen(){
    if(buchungUnvollstaendig()){
        QMessageBox::information(this,"Kein Betrag"," Betrag hinzufuegen");
        return;
    }
    if(ui->radioButtonEinnahme->isChecked()){
        neueEinnahme();
        close();
    }

    else if(ui->radioButtonAusgabe->isChecked()){
        neueAusgabe();
        close();
    }

    else if(ui->radioButtonRechnung->isChecked()){
        neueRechnung();
        close();
    }
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
}

void NeueBuchung::neueEinnahme(){
    QString kategorie = ui->comboBox->currentText();
    QString betrag = ui->betrag->toPlainText();

    QDate date = ui->dateEditDatum->date();
    bool regelmaessig;
    if(ui->radioButtonJa->isChecked()){
        regelmaessig = true;
    }
    else{
        regelmaessig = false;
    }
    QString notes = ui->notes->toPlainText();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    double betragInEuro;
    if(ui->comboBox_2->currentText() == "$"){
        betragInEuro = mainWindow->convertToEurofromUSD(betrag.toDouble());
        mainWindow->einnahmeHinzufuegen(new Einnahme(betragInEuro,date,regelmaessig,notes,kategorie));
    }
    if(ui->comboBox_2->currentText() == "¥"){
        betragInEuro = mainWindow->convertToEurofromJPY(betrag.toDouble());
        mainWindow->einnahmeHinzufuegen(new Einnahme(betragInEuro,date,regelmaessig,notes,kategorie));
    }
    if(ui->comboBox_2->currentText() == "€")mainWindow->einnahmeHinzufuegen(new Einnahme(betrag.toDouble(),date,regelmaessig,notes,kategorie));     //betrag.toDouble mit betragInEuro ersetzen

    QMessageBox::information(this,"Erledigt","Einnahme erfolgreich hinzugefügt");
}

void NeueBuchung::neueAusgabe(){
    QString kategorie = ui->comboBox->currentText();
    QString betrag = ui->betrag->toPlainText();
    QDate date = ui->dateEditDatum->date();
    bool regelmaessig;
    if(ui->radioButtonJa->isChecked()){
        regelmaessig = true;
    }
    else{
        regelmaessig = false;
    }
    QString notes = ui->notes->toPlainText();

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    double betragInEuro;
    if(ui->comboBox_2->currentText() == "$"){
        betragInEuro = mainWindow->convertToEurofromUSD(betrag.toDouble());
        mainWindow->ausgabenHinzufuegen(new Ausgabe(betragInEuro,date,regelmaessig,notes,kategorie));
    }
    if(ui->comboBox_2->currentText() == "¥"){
        betragInEuro = mainWindow->convertToEurofromJPY(betrag.toDouble());
        mainWindow->ausgabenHinzufuegen(new Ausgabe(betragInEuro,date,regelmaessig,notes,kategorie));
    }
    if(ui->comboBox_2->currentText() == "€")mainWindow->ausgabenHinzufuegen(new Ausgabe(betrag.toDouble(),date,regelmaessig,notes,kategorie));

    QMessageBox::information(this,"Erledigt","Ausgabe erfolgreich hinzugefügt");
}

void NeueBuchung::neueRechnung(){
    QString kategorie = ui->comboBox->currentText();
    QString betrag = ui->betrag->toPlainText();
    QDate date = ui->dateEditDatum->date();
    bool regelmaessig;
    if(ui->radioButtonJa->isChecked()){
        regelmaessig = true;
    }
    else{
        regelmaessig = false;
    }
    QDate faelligkeitsdatum = ui->dateEditFaelligkeitsdatum->date();
    QString notes = ui->notes->toPlainText();

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    double betragInEuro;
    if(ui->comboBox_2->currentText() == "$"){
        betragInEuro = mainWindow->convertToEurofromUSD(betrag.toDouble());
        mainWindow->rechnungHinzufuegen(new Rechnung(betragInEuro,date,regelmaessig,notes,kategorie,faelligkeitsdatum,false));
    }
    else if(ui->comboBox_2->currentText() == "¥"){
        betragInEuro = mainWindow->convertToEurofromJPY(betrag.toDouble());
        mainWindow->rechnungHinzufuegen(new Rechnung(betragInEuro,date,regelmaessig,notes,kategorie,faelligkeitsdatum,false));
    }
    else if(ui->comboBox_2->currentText() == "€"){
        mainWindow->rechnungHinzufuegen(new Rechnung(betrag.toDouble(),date,regelmaessig,notes,kategorie,faelligkeitsdatum,false));
    }

   QMessageBox::information(this,"Erledigt","Rechnung erfolgreich hinzugefügt");
}

