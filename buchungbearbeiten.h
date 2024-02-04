#ifndef BUCHUNGBEARBEITEN_H
#define BUCHUNGBEARBEITEN_H

#include <QWidget>

namespace Ui {
class BuchungBearbeiten;
}

class BuchungBearbeiten : public QWidget
{
    Q_OBJECT

public:
    explicit BuchungBearbeiten(QWidget *parent = nullptr);
    ~BuchungBearbeiten();
    void zurueck();
    void loeschen();
    void bearbeiten();
    void suchen();

private:
    Ui::BuchungBearbeiten *ui;
};

#endif // BUCHUNGBEARBEITEN_H
