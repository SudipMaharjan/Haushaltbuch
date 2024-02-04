#include "sparplanbearbeiten.h"
#include "mainwindow.h"
#include "ui_sparplanbearbeiten.h"
#include <QMessageBox>

SparplanBearbeiten::SparplanBearbeiten(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SparplanBearbeiten)
{
    ui->setupUi(this);
    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&SparplanBearbeiten::zurueck);
    connect(ui->pushButtonSparplanLoeschen,&QPushButton::clicked,this,&SparplanBearbeiten::loeschen);
    connect(ui->pushButtonSpeichern,&QPushButton::clicked,this,&SparplanBearbeiten::bearbeiten);
    connect(ui->pushButtonSuchen,&QPushButton::clicked,this,&SparplanBearbeiten::suchen);
}

SparplanBearbeiten::~SparplanBearbeiten()
{
    delete ui;
}

void SparplanBearbeiten::zurueck(){
    close();
}

void SparplanBearbeiten::loeschen(){
    int num = ui->SparplanNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Sparplan* s = mainWindow->getSparplan(num);
    if(s == nullptr){
        QMessageBox::information(this, "nicht gefunden","Sparplan nicht gefunden");
        return;
    }
    else{
        if(s->getZielBetrag() == s->getGesparterBetrag()){
            QMessageBox::information(this, "Betrag schon gespart","Sparplan kann nicht gelöscht werden");
        }
        else{
            mainWindow->delSparplan(num);
        }
    }
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
    close();
}

void SparplanBearbeiten::bearbeiten(){
    int num = ui->SparplanNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Sparplan* s = mainWindow->getSparplan(num);
    if(s == nullptr){
        QMessageBox::information(this, "nicht gefunden","Sparplan nicht gefunden");
        return;
    }
    else{
        double zielBetrag = ui->zielBetrag->text().toDouble();
        QDate zielDatum = ui->dateEditZielDatum->date();
        int sparvariante = ui->comboBox->currentText().toInt();
        s->sparplanBearbeiten(zielBetrag,zielDatum,sparvariante);
        QMessageBox::information(this,"Erledigt","Sparplan erfolgreich bearbeitet");

        QString sp=QString::fromStdString("Sparplan "+to_string(s->getSparplanNr()));
        cout << "sparplan" << sp.toStdString() << endl;
        vector<int> delindexes;
        for(unsigned int i=0;i<mainWindow->ausgaben.size();i++){
            if(mainWindow->ausgaben[i]->getNotes()==sp){
                delindexes.push_back(i);
            }
        }
        std::reverse(delindexes.begin(),delindexes.end());
        for(int &t:delindexes){
            Ausgabe* deleted = mainWindow->ausgaben.at(t);
            mainWindow->ausgaben.erase(mainWindow->ausgaben.begin()+t);
            delete deleted;
        }
        int sparplannummer = num;
        string sparplannotes = "";
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
            sparplannotes = "Sparplan " + to_string(sparplannummer);
            mainWindow->ausgabenHinzufuegen(new Ausgabe(monatsbetrag,day,true,QString::fromStdString(sparplannotes),"Sparen"));
        }
    }
    mainWindow->updateBarchart();
    mainWindow->Piechartjaehrlich();
    close();
}

void SparplanBearbeiten::suchen(){
    int num = ui->SparplanNr->text().toInt();
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    Sparplan* s = mainWindow->getSparplan(num);
    if(s == nullptr){
        QMessageBox::information(this, "nicht gefunden","Sparplan nicht gefunden");
        return;
    }
    else{
        ui->comboBox->setCurrentText(QString::number(s->getSparvariante()));
        ui->zielBetrag->setText(QString::number(s->getZielBetrag()));
        ui->dateEditZielDatum->setDate(s->getZielDatum());
        QList<int> intList = {1, 2, 3};
        for (int intValue : intList) {
            ui->comboBox->addItem(QString::number(intValue));
        }
    }
}

