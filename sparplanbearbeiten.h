#ifndef SPARPLANBEARBEITEN_H
#define SPARPLANBEARBEITEN_H

#include <QWidget>

namespace Ui {
class SparplanBearbeiten;
}

class SparplanBearbeiten : public QWidget
{
    Q_OBJECT

public:
    explicit SparplanBearbeiten(QWidget *parent = nullptr);
    ~SparplanBearbeiten();
    void zurueck();
    void loeschen();
    void bearbeiten();
    void suchen();

private:
    Ui::SparplanBearbeiten *ui;
};

#endif // SPARPLANBEARBEITEN_H

