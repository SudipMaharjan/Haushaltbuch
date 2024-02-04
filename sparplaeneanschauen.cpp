#include "sparplaeneanschauen.h"
#include "qstandarditemmodel.h"
#include "ui_sparplaeneanschauen.h"
#include "mainwindow.h"

SparplaeneAnschauen::SparplaeneAnschauen(QWidget *parent, vector<Sparplan*>&s)
    : QWidget(parent),ui(new Ui::SparplaeneAnschauen)
    , sparplaene(s)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->pushButtonZurueck,&QPushButton::clicked,this,&SparplaeneAnschauen::zurueck);
    createSparplaeneTable();
}

SparplaeneAnschauen::~SparplaeneAnschauen()
{

    for(auto &s: sparplaene){
        delete s;
        s = nullptr;
    }
    delete ui;
}

void SparplaeneAnschauen::zurueck(){
    this->close();
}

void SparplaeneAnschauen::createSparplaeneTable(){
    QStandardItemModel *model = new QStandardItemModel();
    int AnzahlSpalte = 5;
    model->setColumnCount(AnzahlSpalte);
    model->setHorizontalHeaderLabels({ "SparplanNr.","Zielbetrag", "Bereits gespart", "zieldatum", "Sparvariante"});

    for (size_t row = 0; row < sparplaene.size(); ++row) {
        const Sparplan* s = sparplaene[row];

        model->insertRow(row);
        QDate today;
        today=today.currentDate();

        double gbet=0.0;
        MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
        for(unsigned int s=0;s<mainWindow->ausgaben.size();s++){
            if(mainWindow->ausgaben[s]->getNotes()==QString::fromStdString("Sparplan Nr. "+to_string(sparplaene[row]->getSparplanNr())) && mainWindow->ausgaben[s]->getDatum()<=today){
                gbet=gbet+mainWindow->ausgaben[s]->getBetrag();
            }
        }
        cout << "gbet: " << gbet << endl;
        model->setData(model->index(row, 0), s->getSparplanNr());
        model->setData(model->index(row, 1), s->getZielBetrag());
        model->setData(model->index(row, 2), std::round(gbet*100)/100);
        model->setData(model->index(row, 3), s->getZielDatum());
        model->setData(model->index(row, 4), s->getSparvariante());
    }
    ui->tableView->setModel(model);
    ui->tableView->show();
}
