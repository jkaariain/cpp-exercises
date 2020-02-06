// harjoitustyo-04
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QAction>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // Laskee painoindeksin painon ja pituuden perusteella.
    void laske_painoindeksi();

    // Tulkitsee painoindeksin
    void maarita_tulkinta();

    // Lopettaa ohjelman
    void on_actionLopeta_triggered();

    // Asettaa käyttöliittymäkomponenttien
    // arvot samanlaisiksi, kuin ne olivat alussa.
    void on_actionAlkutila_triggered();


private:
    Ui::MainWindow *ui;

    // Radiovalikko sukupuolelle
    QActionGroup *sukupuoli_valikko;
};

#endif // MAINWINDOW_HH
