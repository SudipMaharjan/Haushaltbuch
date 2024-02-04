#ifndef EINNAHME_H
#define EINNAHME_H
#include "buchung.h"
#include <iostream>

using namespace std;

class Einnahme: public Buchung
{
public:
    Einnahme(double b, QDate d, bool r, QString n, QString k);
    Einnahme();
    ~Einnahme();

    QString getKategorie() const;
    double getBetrag() const;
    QDate getDatum() const;
    bool getRegelmaessig() const;
    QString getNotes() const;
    void setKategorie(const QString &value);
    int getBuchungNr() const;
    void einnahmeBearbeiten(double, QDate, bool, QString, QString);

    friend ostream& operator<<(ostream& os, const Einnahme& b);
    friend istream& operator>>(istream& is, Einnahme& b);


private:
    QString kategorie;
};

#endif // EINNAHME_H
