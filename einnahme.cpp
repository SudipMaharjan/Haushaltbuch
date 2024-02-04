#include "einnahme.h"



Einnahme::Einnahme(double b, QDate d, bool r, QString n, QString k) : Buchung(b,d,r,n), kategorie(k)
{

}

Einnahme::Einnahme()
{

}

Einnahme::~Einnahme()
{

}

QString Einnahme::getKategorie() const
{
    return kategorie;
}

void Einnahme::setKategorie(const QString &value)
{
    kategorie = value;
}

double Einnahme::getBetrag() const{
    return Buchung::getBetrag();
}

QDate Einnahme::getDatum() const{
    return Buchung::getDatum();
}

bool Einnahme::getRegelmaessig() const{
    return Buchung::getRegelmaessig();
}

QString Einnahme::getNotes() const{
    return Buchung::getNotes();
}

int Einnahme::getBuchungNr() const{
    return Buchung::getBuchungNr();
}

void Einnahme::einnahmeBearbeiten(double b, QDate d,bool r, QString n,QString k){
    setBetrag(b);
    setDatum(d);
    setRegelmaessig(r);
    setNotes(n);
    kategorie = k;
}

ostream& operator<<(ostream& os, const Einnahme& b){
    os <<b.getBuchungNr()<<" "<< b.getBetrag()<<" "<<b.getDatum().day()<<" "<<b.getDatum().month()<<" "<<b.getDatum().year()<<" "<<b.getRegelmaessig() <<" ";
    os <<b.getKategorie().toStdString() <<" "<< b.getNotes().toStdString();
    return os;
}
istream& operator>>(istream& is, Einnahme& b){
    string output;
    //BuchNR
    is>>output;
    b.setBuchungNr(std::stoi(output));
    //Betrag
    is>>output;
    b.setBetrag(std::stod(output));
    //Datum
    int day, month, year;
    is>>day;
    is>>month;
    is>>year;
    b.setDatum(QDate(year, month, day));
    //Regelmässig
    is>>output;
    bool regel = output == "1";
    b.setRegelmaessig(regel);
    //Kategorie
    is>>output;
    b.setKategorie(QString::fromStdString(output));
    //Notizen
    char name[256];
    is.getline (name, 256);
    QString s = name;
    s.removeFirst();
    b.setNotes(s);

    return is;
}

