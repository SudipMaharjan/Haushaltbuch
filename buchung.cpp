#include "buchung.h"

static int nextNr = 0;

Buchung::Buchung()
{

}

Buchung::Buchung(double b, QDate d, bool r, QString n) :buchungNr(nextNr++), betrag(b),datum(d),regelmaessig(r),notes(n)
{

}

Buchung::~Buchung()
{

}

double Buchung::getBetrag() const
{
    return betrag;
}

QDate Buchung::getDatum() const
{
    return datum;
}

bool Buchung::getRegelmaessig() const
{
    return regelmaessig;
}

QString Buchung::getNotes() const
{
    return notes;
}

int Buchung::getBuchungNr()const{
    return buchungNr;
}

void Buchung::setBuchungNr(int newBuchungNr)
{
    buchungNr = newBuchungNr;
}

void Buchung::setBetrag(double newBetrag)
{
    betrag = newBetrag;
}

void Buchung::setDatum(const QDate &newDatum)
{
    datum = newDatum;
}

void Buchung::setRegelmaessig(bool newRegelmaessig)
{
    regelmaessig = newRegelmaessig;
}

void Buchung::setNotes(const QString &newNotes)
{
    notes = newNotes;
}

