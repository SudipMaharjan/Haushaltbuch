#include "buchungbearbeiten.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "ui_buchungbearbeiten.h"

BuchungBearbeiten::BuchungBearbeiten(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuchungBearbeiten)
{
    ui->setupUi(this);

    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&BuchungBearbeiten::zurueck);
    connect(ui->pushButtonSpeichern,&QPushButton::clicked,this,&BuchungBearbeiten::bearbeiten);
    connect(ui->pushButtonBuchungLoeschen,&QPushButton::clicked,this,&BuchungBearbeiten::loeschen);
    connect(ui->pushButtonSuchen,&QPushButton::clicked,this,&BuchungBearbeiten::suchen);
}

BuchungBearbeiten::~BuchungBearbeiten()
{
    delete ui;
}

void BuchungBearbeiten::zurueck(){
    close();
}

void BuchungBearbeiten::suchen(){
    int num = ui->buchungNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Buchung* b = mainWindow->getBuchung(num);
    if(b == nullptr){
        QMessageBox::information(this, "nicht gefunden","Buchung nicht gefunden");
        return;
    }
    else{
        if(typeid(*b)==typeid(Einnahme)){
            Einnahme* e = dynamic_cast<Einnahme*>(b);
            ui->comboBox->setCurrentText(e->getKategorie());
            ui->betrag->setText(QString::number(e->getBetrag()));
            ui->dateEditDatum->setDate(e->getDatum());
            ui->radioButtonJa->setChecked(e->getRegelmaessig());
            ui->notes->setText(e->getNotes());
            QStringList items = {"Regel", "Einmalig", "Geliehen"};
            ui->comboBox->addItems(items);
        }

        else if(typeid(*b)==typeid(Ausgabe)){
            Ausgabe* a = dynamic_cast<Ausgabe*>(b);
            ui->comboBox->setCurrentText(a->getKategorie());
            ui->betrag->setText(QString::number(a->getBetrag()));
            ui->dateEditDatum->setDate(a->getDatum());

            if(a->getRegelmaessig() == true){
                ui->radioButtonJa->setChecked(true);
            }
            else{
                ui->radioButtonNein->setChecked(true);
            }

            ui->notes->setText(a->getNotes());
            QStringList items = {   "MieteHypothek", "Lebensmittel", "Haushaltsbedarf", "Versorgungsunternehmen", "Transport", "Kleidung", "SchoenheitPflege",
                                 "Gesundheitswesen","Restaurants", "Unterhaltung", "Reisen", "Hobbys", "Bankgebuehren", "Kreditkartenzahlungen", "Investitionen",
                                 "Bildungsausgaben", "Geschenke", "Spenden", "Versicherungen", "UnvorhergeseheneAusgaben" ,"Sparen", "Sonstige"} ;
            ui->comboBox->addItems(items);
        }

        else if(typeid(*b)==typeid(Rechnung)){
            Rechnung* r = dynamic_cast<Rechnung*>(b);
            ui->comboBox->setCurrentText(r->getKategorie());
            ui->betrag->setText(QString::number(r->getBetrag()));
            ui->dateEditDatum->setDate(r->getDatum());
            ui->radioButtonJa->setChecked(r->getRegelmaessig());
            ui->notes->setText(r->getNotes());
            ui->dateEditFaelligkeitsdatum->setDate(r->getFaelligkeitsDatum());

            if(r->getBezahlt() == true){
                ui->radioButtonBezahltJa->setChecked(true);
            }
            else{
                ui->radioButtonBezahltNein->setChecked(true);
            }
            QStringList items = {   "MieteHypothek", "Lebensmittel", "Haushaltsbedarf", "Versorgungsunternehmen", "Transport", "Kleidung", "SchoenheitPflege",
                                 "Gesundheitswesen","Restaurants", "Unterhaltung", "Reisen", "Hobbys", "Bankgebuehren", "Kreditkartenzahlungen", "Investitionen",
                                 "Bildungsausgaben", "Geschenke", "Spenden", "Versicherungen", "UnvorhergeseheneAusgaben" ,"Sparen", "Sonstige"} ;
            ui->comboBox->addItems(items);
        }
        else{
            QMessageBox::information(this, "error","error");
        }
    }
}

void BuchungBearbeiten::loeschen(){
    int num = ui->buchungNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Buchung* b = mainWindow->getBuchung(num);
    if(b == nullptr){
        QMessageBox::information(this, "nicht gefunden","Buchung nicht gefunden");
        return;
    }
    else{
        if(typeid(*b)==typeid(Einnahme)){
            mainWindow->delEinnahme(num);
        }
        else if(typeid(*b)==typeid(Ausgabe)){
            mainWindow->delAusgabe(num);
        }
        else if(typeid(*b)==typeid(Rechnung)){
            mainWindow->delRechnung(num);
        }
    }
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
    close();
}

void BuchungBearbeiten::bearbeiten(){
    int num = ui->buchungNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Buchung* b = mainWindow->getBuchung(num);
    if(b == nullptr){
        QMessageBox::information(this, "nicht gefunden","Buchung nicht gefunden");
        return;
    }
    else{
        if(typeid(*b)==typeid(Einnahme)){
            QString kategorie = ui->comboBox->currentText();
            double betrag = ui->betrag->toPlainText().toDouble();
            QDate datum = ui->dateEditDatum->date();
            bool regelmaessig;
            if(ui->radioButtonJa->isChecked() == true){
                regelmaessig = true;
            }
            else{
                regelmaessig = false;
            }
            QString notes = ui->notes->toPlainText();
            Einnahme* e = dynamic_cast<Einnahme*>(b);
            e->einnahmeBearbeiten(betrag,datum,regelmaessig,notes,kategorie);
            QMessageBox::information(this,"Erledigt","Einnahme erfolgreich bearbeitet");
        }
        else if(typeid(*b)==typeid(Ausgabe)){
            QString kategorie = ui->comboBox->currentText();
            double betrag = ui->betrag->toPlainText().toDouble();
            QDate datum = ui->dateEditDatum->date();
            bool regelmaessig;
            if(ui->radioButtonJa->isChecked() == true){
                regelmaessig = true;
            }
            else{
                regelmaessig = false;
            }
            QString notes = ui->notes->toPlainText();
            Ausgabe* a = dynamic_cast<Ausgabe*>(b);
            a->ausgabeBearbeiten(betrag,datum,regelmaessig,notes,kategorie);
            if(notes.contains("Sparplan ")){

            }

            QMessageBox::information(this,"Erledigt","Ausgabe erfolgreich bearbeitet");
        }
        else if(typeid(*b)==typeid(Rechnung)){
            QString kategorie = ui->comboBox->currentText();
            double betrag = ui->betrag->toPlainText().toDouble();
            QDate datum = ui->dateEditDatum->date();
            bool regelmaessig;
            if(ui->radioButtonJa->isChecked() == true){
                regelmaessig = true;
            }
            else{
                regelmaessig = false;
            }
            QDate faelligkeitsDatum = ui->dateEditFaelligkeitsdatum->date();
            QString notes = ui->notes->toPlainText();
            bool bezahlt;
            if(ui->radioButtonBezahltJa->isChecked() == true){
                bezahlt = true;
            }
            else{
                bezahlt = false;
            }
            Rechnung* r = dynamic_cast<Rechnung*>(b);
            r->rechnungBearbeiten(betrag,datum,regelmaessig,notes,kategorie,faelligkeitsDatum,bezahlt);
            QMessageBox::information(this,"Erledigt","Rechnung erfolgreich bearbeitet");
        }
    }
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
}
