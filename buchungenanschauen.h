#ifndef BUCHUNGENANSCHAUEN_H
#define BUCHUNGENANSCHAUEN_H

#include "ausgabe.h"
#include "einnahme.h"
#include "rechnung.h"
#include <QWidget>

namespace Ui {
class BuchungenAnschauen;
}

class BuchungenAnschauen : public QWidget
{
    Q_OBJECT

public:
    explicit BuchungenAnschauen(QWidget *parent,vector<Einnahme*>e,vector<Ausgabe*>a,vector<Rechnung*>r);
    ~BuchungenAnschauen();
    void zurueck();
    void createEinnahmenTable();
    void createAusgabenTable();
    void createRechnungenTable();

private:
    Ui::BuchungenAnschauen *ui;
    vector<Einnahme*> einnahmen;
    vector<Ausgabe*> ausgaben;
    vector<Rechnung*> rechnungen;
};

#endif // BUCHUNGENANSCHAUEN_H
