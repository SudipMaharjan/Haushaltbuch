#include "ausgabe.h"



Ausgabe::Ausgabe(double b, QDate d, bool r, QString n, QString k) : Buchung(b,d,r,n),kategorie(k)
{

}

Ausgabe::Ausgabe()
{

}

Ausgabe::~Ausgabe()
{

}

void Ausgabe::setAusgKategorie(QString newAusgKategorie)
{
    kategorie = newAusgKategorie;
}

QString Ausgabe::getKategorie() const
{
    return kategorie;
}

double Ausgabe::getBetrag() const{
    return Buchung::getBetrag();
}

QDate Ausgabe::getDatum() const{
    return Buchung::getDatum();
}

bool Ausgabe::getRegelmaessig() const{
    return Buchung::getRegelmaessig();
}

QString Ausgabe::getNotes() const{
    return Buchung::getNotes();
}

int Ausgabe::getBuchungNr() const{
    return Buchung::getBuchungNr();
}

void Ausgabe::ausgabeBearbeiten(double b, QDate d,bool r, QString n,QString k){
    setBetrag(b);
    setDatum(d);
    setRegelmaessig(r);
    setNotes(n);
    kategorie = k;
}

ostream& operator<<(ostream& os, const Ausgabe& a){
    os <<a.getBuchungNr()<<" "<< a.getBetrag()<<" "<<a.getDatum().day()<<" "<<a.getDatum().month()<<" "<<a.getDatum().year()<<" "<<a.getRegelmaessig() <<" ";
    os << a.getKategorie().toStdString() <<" "<< a.getNotes().toStdString();
    return os;
}

istream& operator>>(istream& is, Ausgabe& a){
    string output;
    //BuchNR
    is>>output;
    a.setBuchungNr(std::stoi(output));
    //Betrag
    is>>output;
    a.setBetrag(std::stod(output));
    //Datum
    int day, month, year;
    is>>day;
    is>>month;
    is>>year;
    a.setDatum(QDate(year, month, day));
    //Regelmässig
    is>>output;
    bool regel = output == "1";
    a.setRegelmaessig(regel);
    //Kategorie
    is>>output;
    a.setAusgKategorie(QString::fromStdString(output));
    //Notizen
    char name[256];
    is.getline (name, 256);
    QString s = name;
    s.removeFirst();
    a.setNotes(s);

    return is;
}
