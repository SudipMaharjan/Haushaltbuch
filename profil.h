#ifndef PROFIL_H
#define PROFIL_H

#include <QWidget>

using namespace std;

namespace Ui {
class Profil;
}

class Profil : public QWidget
{
    Q_OBJECT

public:
    explicit Profil(QWidget *parent = nullptr);
    ~Profil();
    Profil();
    Profil(string name, string waehrung);

    string getName() const;
    void setName(const string &value);

    double getGespartes() const;
    void setGespartes(double value);

    void zurueck();
    void anpassen();
    void showLevel();
    void addProfil(string, string);

    friend ostream& operator<<(ostream& os, const Profil& p);
    friend istream& operator>>(istream& is, Profil& p);

    void showDetails();
    string getWaehrung() const;
    void setWaehrung(const string &newWaehrung);

private:
    Ui::Profil *ui;
    string name;
    double gespartes;
    string waehrung;
};

#endif // PROFIL_H
