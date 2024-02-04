#ifndef BUCHUNG_H
#define BUCHUNG_H
#include <iostream>
#include <QDate>

using namespace std;


class Buchung
{
public:
    Buchung();
    virtual ~Buchung();
    Buchung(double b, QDate d, bool r, QString n);
    virtual double getBetrag() const;
    virtual QDate getDatum() const;
    virtual bool getRegelmaessig() const;
    virtual QString getNotes() const;
    virtual int getBuchungNr()const;


    void setBuchungNr(int newBuchungNr);
    void setBetrag(double newBetrag);
    void setDatum(const QDate &newDatum);
    void setRegelmaessig(bool newRegelmaessig);
    void setNotes(const QString &newNotes);

private:
    int buchungNr;
    double betrag;
    QDate datum;
    bool regelmaessig;
    QString notes;
};

#endif // BUCHUNG_H
