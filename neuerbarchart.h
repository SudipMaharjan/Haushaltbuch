#ifndef NEUERBARCHART_H
#define NEUERBARCHART_H


#include <QBarSeries>
#include <QBarSet>
#include <einnahme.h>
#include <ausgabe.h>
#include <QChartView>
#include "qbarcategoryaxis.h"
#include "qvalueaxis.h"

class meinBarchart
{
private:
    QChart* c;
    QChartView* r;
    QBarSet* e;
    QBarSet* a;
    QBarSet* s;
    QBarSeries* series;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
    QStringList categories;
    string Währung;
    double EUR;
    double YEN;
    double USD;

public:

    meinBarchart(vector<Einnahme*> einnahmenListe,vector<Ausgabe*> ausgabenListe, string Währung,double newEUR, double newYEN, double newUSD);
    ~meinBarchart();
    QChartView *getR() const;
    void setR(QChartView *newR);
    void update(vector<Einnahme*> einnahmenListe,vector<Ausgabe*> ausgabenListe, string Währung,double newEUR, double newYEN, double newUSD);
    double convertToUSD(double euroAmount);
    double convertToJPY(double euroAmount);
    void processEinnahmenListe(vector<Einnahme*>,vector<int>&,double&);
    void processAusgabenListe(vector<Ausgabe*>,vector<int>&,double&);
    void calculateSparRate(vector<int>& , vector<int>& , vector<int>&,double& , double&, double&);
    void setupChart(double&);
    void addNewData();

    string getWährung() const;
    void setWährung(const string &newWährung);
    double getYEN() const;
    double getEUR() const;
    double getUSD() const;
};
#endif // NEUERBARCHART_H
