#ifndef PAAIKKUNA_HH
#define PAAIKKUNA_HH

#include <QWidget>

namespace Ui {
class Paaikkuna;
}

class Paaikkuna : public QWidget
{
    Q_OBJECT

public:
    explicit Paaikkuna(QWidget *parent = 0);
    ~Paaikkuna();

public slots:
    void nollaa_kaikki_arvot();
    void laske_mailia_tunnissa();

private:
    Ui::Paaikkuna *ui;
};

#endif // PAAIKKUNA_HH
