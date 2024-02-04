#ifndef AUSGABE_H
#define AUSGABE_H
#include "buchung.h"
#include <iostream>

using namespace std;



class Ausgabe: public Buchung
{

public:
    Ausgabe(double b, QDate d, bool r, QString n, QString ausgKategorien);
    Ausgabe();
    ~Ausgabe();
    QString getKategorie() const;
    void setAusgKategorie(QString newAusgKategorie);

    double getBetrag() const;
    QDate getDatum() const;
    bool getRegelmaessig() const;
    QString getNotes() const;
    int getBuchungNr() const;

    void ausgabeBearbeiten(double, QDate, bool, QString,QString);

    friend ostream& operator<<(ostream& os, const Ausgabe& a);
    friend istream& operator>>(istream& is, Ausgabe& a);



private:
    QString kategorie;
};

#endif // AUSGABE_H
