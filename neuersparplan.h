#ifndef NEUERSPARPLAN_H
#define NEUERSPARPLAN_H

#include <QWidget>

namespace Ui {
class NeuerSparplan;
}

class NeuerSparplan : public QWidget
{
    Q_OBJECT

public:
    explicit NeuerSparplan(QWidget *parent = nullptr);
    ~NeuerSparplan();
    void zurueck();
    void bestaetigen();
    bool sparplanUnvollstaendig();

private:
    Ui::NeuerSparplan *ui;
};

#endif // NEUERSPARPLAN_H
