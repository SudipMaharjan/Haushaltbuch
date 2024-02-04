#include "neuersparplan.h"
#include "mainwindow.h"
#include "ui_neuersparplan.h"
#include <QMessageBox>

NeuerSparplan::NeuerSparplan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NeuerSparplan)
{
    ui->setupUi(this);

    QList<int> intList = {1};
    for (int intValue : intList) {
        ui->comboBox->addItem(QString::number(intValue));
    }
    ui->dateEditZielDatum->setDate(QDate::currentDate());

    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&NeuerSparplan::zurueck);
    connect(ui->pushButtonBestaetigen,&QPushButton::clicked,this,&NeuerSparplan::bestaetigen);
}

NeuerSparplan::~NeuerSparplan()
{
    delete ui;
}

void NeuerSparplan::zurueck(){
    close();
}

bool NeuerSparplan::sparplanUnvollstaendig(){
    QString betrag = ui->zielBetrag->text();
    if(betrag == ""){
        return true;
    }
    return false;
}

void NeuerSparplan::bestaetigen(){
    if(sparplanUnvollstaendig()){
        QMessageBox::information(this,"Kein Betrag"," Betrag hinzufuegen");
        return;
    }
    double zielBetrag = ui->zielBetrag->text().toDouble();
    QDate zielDatum = ui->dateEditZielDatum->date();
    int sparvariant = ui->comboBox->currentText().toInt();
    int sparplannummer = 0;
    string sparplannotes = "";

    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());

    Sparplan*sp = new Sparplan(zielBetrag,zielDatum,sparvariant);
    sparplannummer=sp->getSparplanNr();
    mainWindow->sparplanHinzufuegen(sp);
    QMessageBox::information(this,"Erledigt","Sparplan erfolgreich hinzugefügt");

    QDate today;
    QDate day;
    today=today.currentDate();
    day=today;
    int dist = today.daysTo(zielDatum);
    double sparzeiten = dist/30; //wie oft muss montasbetrag abgebucht werden?
    if(sparzeiten<=1){
        sparzeiten=1;
    }
    double monatsbetrag = zielBetrag/sparzeiten; //monatsbetrag wird alle 30 tage abgebucht
    monatsbetrag=round(monatsbetrag*100)/100;
    int sparzeiten2 = (int)sparzeiten;
    for(int i=0;i<sparzeiten2;i++){
        if(dist>30)
            day = day.addDays(30);
        else
            day = zielDatum;
        sparplannotes = "Sparplan Nr. " + to_string(sparplannummer);
        mainWindow->ausgabenHinzufuegen(new Ausgabe(monatsbetrag,day,true,QString::fromStdString(sparplannotes),"Sparen"));
    }
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
    close();
}
