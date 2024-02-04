#include "buchungenanschauen.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "ui_buchungenanschauen.h"

BuchungenAnschauen::BuchungenAnschauen(QWidget *parent, vector<Einnahme*>e,vector<Ausgabe*>a,vector<Rechnung*>r) :
    QWidget(parent),ui(new Ui::BuchungenAnschauen),einnahmen(e),ausgaben(a),
    rechnungen(r)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->radioButtonEinnahmen,&QPushButton::toggled,this, &BuchungenAnschauen::createEinnahmenTable);
    connect(ui->radioButtonAusgaben,&QPushButton::toggled,this, &BuchungenAnschauen::createAusgabenTable);
    connect(ui->radioButtonRechnungen,&QPushButton::toggled,this, &BuchungenAnschauen::createRechnungenTable);
    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&BuchungenAnschauen::zurueck);

    createEinnahmenTable();
    ui->radioButtonEinnahmen->setChecked(true);
}

BuchungenAnschauen::~BuchungenAnschauen()
{

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
    delete ui;
}

void BuchungenAnschauen::zurueck(){
    close();
}

void BuchungenAnschauen::createEinnahmenTable(){
    QStandardItemModel *model = new QStandardItemModel();
    int AnzahlSpalte = 6;
    model->setColumnCount(AnzahlSpalte);
    model->setHorizontalHeaderLabels({ "BuchungNr.","Kategorie", "Datum", "regelmaessig?", "Notes", "Betrag" });

    for (size_t row = 0; row < einnahmen.size(); ++row) {
        const Einnahme* e = einnahmen[row];

        model->insertRow(row);

        model->setData(model->index(row, 0), e->getBuchungNr());

        model->setData(model->index(row, 1), e->getKategorie());
        model->setData(model->index(row, 2), e->getDatum());
        if(e->getRegelmaessig()){
            model->setData(model->index(row, 3), "ja");
        }
        else{
            model->setData(model->index(row, 3), "nein");
        }
        model->setData(model->index(row, 4), e->getNotes());
        model->setData(model->index(row, 5), e->getBetrag());
    }
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void BuchungenAnschauen::createAusgabenTable(){
    QStandardItemModel *model = new QStandardItemModel();
    int AnzahlSpalte = 6;
    model->setColumnCount(AnzahlSpalte);
    model->setHorizontalHeaderLabels({"BuchungNr.", "Kategorie", "Datum", "regelmaessig?", "Notes", "Betrag" });

    for (size_t row = 0; row < ausgaben.size(); ++row) {
        const Ausgabe* a = ausgaben[row];

        model->insertRow(row);

        model->setData(model->index(row, 0), a->getBuchungNr());
        model->setData(model->index(row, 1), a->getKategorie());
        model->setData(model->index(row, 2), a->getDatum());
        if(a->getRegelmaessig()){
            model->setData(model->index(row, 3), "ja");
        }
        else{
            model->setData(model->index(row, 3), "nein");
        }
        model->setData(model->index(row, 4), a->getNotes());
        model->setData(model->index(row, 5), a->getBetrag());
    }
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void BuchungenAnschauen::createRechnungenTable(){
    QStandardItemModel *model = new QStandardItemModel();
    int AnzahlSpalte = 8;
    model->setColumnCount(AnzahlSpalte);
    model->setHorizontalHeaderLabels({"BuchungNr.", "Kategorie", "Datum", "regelmaessig?","Faelligkeitsdatum","bezahlt?", "Notes", "Betrag" });

    for (size_t row = 0; row < rechnungen.size(); ++row) {
        const Rechnung* r = rechnungen[row];

        model->insertRow(row);

        model->setData(model->index(row, 0), r->getBuchungNr());
        model->setData(model->index(row, 1), r->getKategorie());
        model->setData(model->index(row, 2), r->getDatum());
        if(r->getRegelmaessig()){
            model->setData(model->index(row, 3), "ja");
        }
        else{
            model->setData(model->index(row, 3), "nein");
        }
        model->setData(model->index(row, 4), r->getFaelligkeitsDatum());
        if(r->getBezahlt()){
            model->setData(model->index(row, 5), "ja");
        }
        else{
            model->setData(model->index(row, 5), "nein");
        }
        model->setData(model->index(row, 6), r->getNotes());
        model->setData(model->index(row, 7), r->getBetrag());

    }
    ui->tableView->setModel(model);
    ui->tableView->show();
}
