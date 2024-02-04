#include "rechnung.h"

Rechnung::Rechnung()
{

}
Rechnung::Rechnung(double b, QDate d, bool r, QString n, QString k, QDate f, bool be)
    : Buchung(b,d,r,n),kategorie(k), faelligkeitsDatum(f),bezahlt(be)
{

}

Rechnung::~Rechnung()
{

}

double Rechnung::getBetrag() const{
    return Buchung::getBetrag();
}

QDate Rechnung::getDatum() const{
    return Buchung::getDatum();
}

bool Rechnung::getRegelmaessig() const{
    return Buchung::getRegelmaessig();
}

QString Rechnung::getNotes() const{
    return Buchung::getNotes();
}

QString Rechnung::getKategorie() const{
    return kategorie;
}

QDate Rechnung::getFaelligkeitsDatum() const
{
    return faelligkeitsDatum;
}

bool Rechnung::getBezahlt() const
{
    return bezahlt;
}

int Rechnung::getBuchungNr() const{
    return Buchung::getBuchungNr();
}

void Rechnung::rechnungBearbeiten(double b, QDate d,bool r, QString n,QString k, QDate f, bool be){
    setBetrag(b);
    setDatum(d);
    setRegelmaessig(r);
    setNotes(n);
    kategorie = k;
    faelligkeitsDatum = f;
    bezahlt = be;
}

void Rechnung::setKategorie(const QString &newKategorie)
{
    kategorie = newKategorie;
}

void Rechnung::setFaelligkeitsDatum(const QDate &newFaelligkeitsDatum)
{
    faelligkeitsDatum = newFaelligkeitsDatum;
}

void Rechnung::setBezahlt(bool newBezahlt)
{
    bezahlt = newBezahlt;
}

ostream& operator<<(ostream& os, const Rechnung& r){
    os<<string(to_string(r.getBuchungNr()) + " " + to_string(r.getBetrag()) + " " + to_string(r.getDatum().day()) + " " + to_string(r.getDatum().month()) + " " + to_string(r.getDatum().year()) + " " + to_string(r.getRegelmaessig()) + " " + r.getKategorie().toStdString() + " " + to_string(r.getFaelligkeitsDatum().day()) + " " + to_string(r.getFaelligkeitsDatum().month()) + " " + to_string(r.getFaelligkeitsDatum().year()) + " " + to_string(r.getBezahlt()) + " " + r.getNotes().toStdString());
    return os;
}

istream& operator>>(istream& is, Rechnung& r){
    string output;
    //BuchNR
    is>>output;
    r.setBuchungNr(std::stoi(output));
    //Betrag
    is>>output;
    r.setBetrag(std::stod(output));
    //Datum
    int day, month, year;
    is>>day;
    is>>month;
    is>>year;
    r.setDatum(QDate(year, month, day));
    //Regelmässig
    is>>output;
    bool regel = output == "1";
    r.setRegelmaessig(regel);
    //Kategorie
    is>>output;
    r.setKategorie(QString::fromStdString(output));
    //FaelligkeitsDatum
    is>>day;
    is>>month;
    is>>year;
    r.setFaelligkeitsDatum(QDate(year, month, day));
    //Bezahlt
    is>>output;
    regel = output == "1";
    r.setBezahlt(regel);
    //Notizen
    char name[256];
    is.getline (name, 256);
    QString s = name;
    s.removeFirst();
    r.setNotes(s);

    return is;
}
