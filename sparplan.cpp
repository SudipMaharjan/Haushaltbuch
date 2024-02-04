#include "sparplan.h"

static int nextSparplanNr = 1;

Sparplan::Sparplan(double zielBet, QDate zielDat, int sparvar): zielBetrag(zielBet), zielDatum(zielDat), sparvariante(sparvar){
    sparplanNr = nextSparplanNr++;
    gesparterBetrag=0;
    QDate today;
    today=today.currentDate();
    int dist = today.daysTo(zielDatum);
    sparzeiten = dist/30; //wie oft muss montasbetrag abgebucht werden?
    if(sparzeiten<=1)
        sparzeiten=1;

    monatsbetrag = zielBet/sparzeiten; //monatsbetrag wird alle 30 tage abgebucht
    monatsbetrag = round(monatsbetrag*100)/100;
    /*cout << "dist" << dist << endl;
    cout << "monatsbetrag" << monatsbetrag << endl;
    cout << "sparzeiten" << sparzeiten << endl;
    cout << "zielbet" << zielBet << endl;
    cout << "today" << today.day() << "." << today.month() << "." << today.year() << endl;
    cout << "zielDatum" << zielDatum.day() << "." << zielDatum.month() << "." << zielDatum.year() << endl;*/
    //gesparterBetrag+=monatsbetrag;
}

Sparplan::Sparplan(){}

void Sparplan::sparplanBearbeiten(double neuZielBet, QDate neuZielDat, int neuSparVar){
    zielBetrag=neuZielBet;
    zielDatum=neuZielDat;
    QDate today;
    today=today.currentDate();
    int dist = today.daysTo(zielDatum);
    sparzeiten = dist/30; //wie oft muss montasbetrag abgebucht werden?
    monatsbetrag = (zielBetrag-gesparterBetrag)/sparzeiten; //monatsbetrag wird alle 30 tage abgebucht
    if(sparzeiten<=1)
        sparzeiten=1;
    sparvariante = neuSparVar;
}

void Sparplan::zusatzzahlen(double betrag){
    //nur bei sparvariante 3 möglich, button wird einfach in ui nicht angezeigt
    gesparterBetrag += betrag;
    QDate today;
    today.currentDate();
    int dist = today.daysTo(zielDatum);
    double sparzeiten = dist/30; //wie oft muss montasbetrag abgebucht werden?
    if(sparzeiten<=1)
        sparzeiten=1;
    monatsbetrag = (zielBetrag-gesparterBetrag)/sparzeiten; //monatsbetrag wird alle 30 tage abgebucht
}

int Sparplan::getSparplanNr() const
{
    return sparplanNr;
}

int Sparplan::getSparvariante() const
{
    return sparvariante;
}

double Sparplan::getSparzeiten() const
{
    return sparzeiten;
}

double Sparplan::getGesparterBetrag() const
{
    double gesp=zielBetrag;
    QDate today;
    today = today.currentDate();
    int dist=today.daysTo(zielDatum);
    if(dist==0)
        return gesp;
    int r=dist/30;
    for(int i=0;i<=r;i++){
        gesp=gesp-monatsbetrag;
    }
    if(gesp<0.0)
        gesp=0.0;
    return gesp;
}

void Sparplan::setGesparterBetrag(double newGesparterBetrag)
{
    gesparterBetrag = newGesparterBetrag;
}

double Sparplan::getMonatsbetrag() const
{
    return monatsbetrag;
}

void Sparplan::setMonatsbetrag(double newMonatsbetrag)
{
    monatsbetrag = newMonatsbetrag;
}

void Sparplan::setZielBetrag(double newZielBetrag)
{
    zielBetrag = newZielBetrag;
}

void Sparplan::setZielDatum(const QDate &newZielDatum)
{
    zielDatum = newZielDatum;
}

void Sparplan::setSparvariante(int newSparvariante)
{
    sparvariante = newSparvariante;
}

QDate Sparplan::getZielDatum() const
{
    return zielDatum;
}

double Sparplan::getZielBetrag() const
{
    return zielBetrag;
}

void Sparplan::setSparplanNr(int nr){
    sparplanNr=nr;
}

ostream& operator<<(ostream& os, const Sparplan& s){
    os<<string(to_string(s.getSparplanNr())+" "+to_string(s.getGesparterBetrag()) + " " + to_string(s.getZielBetrag()) + " " + to_string(s.getZielDatum().day()) + " " + to_string(s.getZielDatum().month()) + " " + to_string(s.getZielDatum().year()) + " " + to_string(s.getMonatsbetrag()) + " " + to_string(s.getSparvariante()));
    return os;
}
istream& operator>>(istream& is, Sparplan& s){
    string output;
    //SparplanNr
    is>>output;
    s.setSparplanNr(std::stoi(output));
    //GesparterBetrag
    is>>output;
    s.setGesparterBetrag(std::stod(output));
    //ZielBetrag
    is>>output;
    s.setZielBetrag(std::stod(output));
    //ZielDatum
    int day, month, year;
    is>>day;
    is>>month;
    is>>year;
    s.setZielDatum(QDate(year, month, day));
    //MonatsBetrag
    is>>output;
    s.setMonatsbetrag(std::stod(output));
    //Sparvariante
    is>>output;
    s.setSparvariante(std::stoi(output));

    return is;
}
