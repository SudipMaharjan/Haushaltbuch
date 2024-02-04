#ifndef SPARPLAENEANSCHAUEN_H
#define SPARPLAENEANSCHAUEN_H

#include "sparplan.h"
#include <QWidget>

namespace Ui {
class SparplaeneAnschauen;
}

class SparplaeneAnschauen : public QWidget
{
    Q_OBJECT

public:
    explicit SparplaeneAnschauen(QWidget *parent,vector<Sparplan*>&s);
    ~SparplaeneAnschauen();
    void zurueck();
    void createSparplaeneTable();

private:
    Ui::SparplaeneAnschauen *ui;
    vector<Sparplan*>sparplaene;
};

#endif // SPARPLAENEANSCHAUEN_H
