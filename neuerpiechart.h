#ifndef NEUERPIECHART_H
#define NEUERPIECHART_H

#include "ausgabe.h"
#include "qchartview.h"
#include <QPieSeries>
#include <QPieSlice>
#include <QStringList>


class meinPiechart {

private:
    QPieSeries* s;
    QChart* ch;
    QChartView* r;
    vector<Ausgabe*> ausgabenListe;
    string Währung;
    double EUR;
    double YEN;
    double USD;
    int Summe = 0;

public:
    meinPiechart(vector<Ausgabe*> ausgabenListe, string newWährung, double newEUR, double newYEN, double newUSD);
    ~meinPiechart();
    QChartView* getR() const;
    void updatePiechart(vector<Ausgabe*> ausgabenListe, string newWährung, double newEUR, double newYEN, double newUSD);
    void statusChange(vector<Ausgabe *> ausgabenListe);
    vector<Ausgabe *> getAusgabenListe() const;
    void setAusgabenListe(const vector<Ausgabe *> &newAusgabenListe);
    string getWährung() const;
    void setWährung(const string &newWährung);
    double getEUR() const;
    double getYEN() const;
    double getUSD() const;
    double convertToUSD(double euroAmount);
    double convertToJPY(double euroAmount);
    int getSumme() const;
    void setSumme(int newSumme);
    void editDetails();
    void addSlice(const string &, double);
    void convertAndAddSlice(const string& kategorie, double betrag);
};

#endif // NEUERPIECHART_H

