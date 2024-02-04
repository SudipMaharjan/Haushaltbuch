#ifndef NEUEBUCHUNG_H
#define NEUEBUCHUNG_H

#include <QWidget>
using namespace std;
namespace Ui {
class NeueBuchung;
}

class NeueBuchung : public QWidget
{
    Q_OBJECT

public:
    explicit NeueBuchung(QWidget *parent = nullptr);
    ~NeueBuchung();
    void populateComboBox();
    void zurueck();
    void bestaetigen();
    void neueEinnahme();
    void neueAusgabe();
    void neueRechnung();
    bool buchungUnvollstaendig();


    double convertToEurofromUSD(double usdAmount);
    double convertToEurofromJPY(double jpyAmount);
private:
    Ui::NeueBuchung *ui;

};

#endif // NEUEBUCHUNG_H
