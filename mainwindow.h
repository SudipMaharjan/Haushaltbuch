#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ausgabe.h"
#include "einnahme.h"
#include "neuerbarchart.h"
#include "neuerpiechart.h"
#include "profil.h"
#include "rechnung.h"
#include "sparplan.h"
#include <QMainWindow>
#include <QResizeEvent>
#include <vector>
#include <iostream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void neueBuchung();
    void buchungAnschauen();
    void ProfilAnzeigen();
    void buchungBearbeiten();
    void neuerSparplan();
    void sparplanBearbeiten();
    void einnahmeHinzufuegen(Einnahme*);
    void ausgabenHinzufuegen(Ausgabe*);
    void rechnungHinzufuegen(Rechnung*);
    void sparplanHinzufuegen(Sparplan*);
    void einnahmeBearbeiten(QString kategorie,double betrag, QDate datum,bool regelmaessig, QString notes);
    void sparplaeneAnschauen();

    void Piecharttaeglich();
    void Piechartmonatlich();
    void Piechartjaehrlich();



    void delRechnung(int i);
    void delAusgabe(int i);
    void delEinnahme(int i);
    void delSparplan(int i);

    Buchung* getBuchung(int);
    Sparplan* getSparplan(int);
    Profil* getProfil();
    void refresh();
    void addBarchartDetails();
    void updateBarchart();

    int getIndex(int);
    int getSparplanIndex(int);
    void setMyPiechart(meinPiechart *newMyPiechart);

    void save();
    void load();

    void addBeispielBuchung();


    void setDollarToYen(double newDollarToYen);
    void setDollarToDollar(double newDollarToDollar);
    void setDollarToEuro(double newEuro);
    double getEuro() const;
    double getDollar() const;
    double getYen() const;

    double convertToEurofromUSD(double usdAmount);
    double convertToEurofromJPY(double jpyAmount);

    vector<Sparplan*> sparplaene;
    vector<Ausgabe*> ausgaben;
    void getExchangeRates(const QString &apiKey);
    double convertToUSD(double euroAmount);
    double convertToJPY(double euroAmount);
    void Barchartbauen();
    void createPiechart();
    void showPiechartDesign();

private:
    Ui::MainWindow *ui;
    vector<Einnahme*> einnahmen;
    vector<Rechnung*> rechnungen;
    Profil* myProfil;
    meinPiechart* myPiechart;
    meinBarchart* myBarchart;
    QChartView* myChartPie;
    QChartView* myChartBar;
    double Dollar;
    double Yen;
    double Euro;
    QString apiKey = "fxa_live_Smu3ilvdiFePYMDQmCTtfv7s7HGgslIIKUyuRQPF";

};
#endif // MAINWINDOW_H
