#ifndef SPARPLAN_H
#define SPARPLAN_H
#include <iostream>
#include <QDate>

using namespace std;

class Sparplan
{
public:
    Sparplan(double zielBet, QDate zielDat, int sparvar);
    Sparplan();

    friend ostream& operator<<(ostream& os, const Sparplan& s);
    friend istream& operator>>(istream& is, Sparplan& s);

    void sparplanBearbeiten(double neuZielBet, QDate neuZielDat, int neuSparVar);
    void zusatzzahlen(double betrag); //bei sparvariante 3 kann mehr gespart werden -> zusatzzahlen

    int getSparplanNr() const;
    int getSparvariante() const;
    QDate getZielDatum() const;
    double getZielBetrag() const;
    double getSparzeiten() const;

    double getGesparterBetrag() const;
    void setGesparterBetrag(double newGesparterBetrag);

    double getMonatsbetrag() const;
    void setMonatsbetrag(double newMonatsbetrag);
    void setSparplanNr(int nr);

    void setZielBetrag(double newZielBetrag);

    void setZielDatum(const QDate &newZielDatum);

    void setSparvariante(int newSparvariante);

private:
    int sparplanNr;
    double gesparterBetrag;
    double zielBetrag;
    QDate zielDatum;
    double monatsbetrag;
    int sparvariante;
    double sparzeiten;
    /* Bitte auch speichern
     * Sparvarianten:
     * 1 = montal. gleicher Betrag
     * 2 = einnahmen-ausgaben am ende des montas kalkuliert //entfernt
     * 3 = monatl. gleicher Betrag, kann erhöht werden -> monatl. Betrag muss neu berechnet werden
     */

};

#endif // SPARPLAN_H
