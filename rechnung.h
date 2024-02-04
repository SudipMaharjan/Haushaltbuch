#ifndef RECHNUNG_H
#define RECHNUNG_H
#include "buchung.h"
#include <iostream>

using namespace std;

class Rechnung: public Buchung
{
public:
    Rechnung();
    Rechnung(double b, QDate d, bool r, QString n, QString k, QDate f, bool be);
    ~Rechnung();
    double getBetrag() const;
    QDate getDatum() const;
    bool getRegelmaessig() const;
    QString getNotes() const;
    QString getKategorie() const;
    QDate getFaelligkeitsDatum() const;
    bool getBezahlt() const;
    int getBuchungNr() const;
    void rechnungBearbeiten(double, QDate,bool, QString, QString, QDate, bool);

    friend ostream& operator<<(ostream& os, const Rechnung& r);
    friend istream& operator>>(istream& is, Rechnung& r);


    void setKategorie(const QString &newKategorie);

    void setFaelligkeitsDatum(const QDate &newFaelligkeitsDatum);

    void setBezahlt(bool newBezahlt);

private:
    QString kategorie;
    QDate faelligkeitsDatum;
    bool bezahlt;
};

#endif // RECHNUNG_H
