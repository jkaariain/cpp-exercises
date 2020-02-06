// harjoitustyo-04
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Luo QActionGroup sukupuolelle.
    sukupuoli_valikko = new QActionGroup(this);

    // Aseta painikkeet merkattavaksi.
    ui->actionMies->setCheckable(true);
    ui->actionNainen->setCheckable(true);

    // Lisää painikkeiden toiminnot luotuun QActionGroup olioon.
    ui->actionMies->setActionGroup(sukupuoli_valikko);
    ui->actionNainen->setActionGroup(sukupuoli_valikko);

    ui->actionNainen->setChecked(true); // Aseta sukupuoleksi nainen

    // Laske painoindeksi, kun painoa tai pituutta muutetaan.
    connect(ui->spinBox_paino, SIGNAL(valueChanged(int)),
            this, SLOT(laske_painoindeksi()));
    connect(ui->spinBox_pituus, SIGNAL(valueChanged(int)),
            this, SLOT(laske_painoindeksi()));

    // Kun kayttaja vaihtaa sukupuolta, maarita tulkinta uudestaan.
    connect(ui->actionNainen, SIGNAL(triggered(bool)),
            this, SLOT(maarita_tulkinta()));
    connect(ui->actionMies, SIGNAL(triggered(bool)),
            this, SLOT(maarita_tulkinta()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLopeta_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAlkutila_triggered()
{
    ui->spinBox_paino->setValue(0);
    ui->spinBox_pituus->setValue(0);
    ui->actionNainen->setChecked(true);
    ui->label_valittu_sukupuoli->setText("nainen");
    ui->label_painoindeksi_maaritelty->setText("-");
    ui->label_tulkinta_maaritelty->setText("-");
}

void MainWindow::laske_painoindeksi()
{
    float paino = ui->spinBox_paino->value();

    // Muunna senttimetrit metreiksi.
    float pituus = ui->spinBox_pituus->value() * 0.01f;

    // Jos joko paino tai pituus on nolla, aseta painoindeksi ja tulkinta
    // merkkijonoksi '-' ja lopeta aliohjelman suoritus.
    if (paino == 0 || pituus == 0){
        ui->label_painoindeksi_maaritelty->setText("-");
        ui->label_tulkinta_maaritelty->setText("-");
        return;
    }

    // Laske painoindeksi
    float bmi = paino / (pituus * pituus);
    ui->label_painoindeksi_maaritelty->setText(QString::number(bmi));

    maarita_tulkinta();
}

void MainWindow::maarita_tulkinta()
{
    // Aseta valitun sukupuolen teksti
    if (ui->actionNainen->isChecked())
        ui->label_valittu_sukupuoli->setText("nainen");
    else if (ui->actionMies->isChecked())
        ui->label_valittu_sukupuoli->setText("mies");

    // Jos joko paino tai pituus on nolla, aseta painoindeksi ja tulkinta
    // merkkijonoksi '-' ja lopeta aliohjelman suoritus.
    if (ui->spinBox_paino->value() == 0 || ui->spinBox_pituus->value() == 0){
        ui->label_painoindeksi_maaritelty->setText("-");
        ui->label_tulkinta_maaritelty->setText("-");
        return;
    }

    float bmi = ui->label_painoindeksi_maaritelty->text().toFloat();

    // Aseta tulkinnan teksti
    if (ui->actionNainen->isChecked()){
        if (bmi <= 19.1f)
            ui->label_tulkinta_maaritelty->setText("alipainoa");
        else if (bmi <= 25.8f && bmi > 19.1f)
            ui->label_tulkinta_maaritelty->setText("normaali");
        else if (bmi <= 27.3f && bmi > 25.8f)
            ui->label_tulkinta_maaritelty->setText("lievää ylipainoa");
        else if (bmi <= 32.2f && bmi > 27.3f)
            ui->label_tulkinta_maaritelty->setText("ylipainoa");
        else if (bmi > 32.2f)
            ui->label_tulkinta_maaritelty->setText("paljon ylipainoa");
    } else if (ui->actionMies->isChecked()){
        if (bmi <= 20.7f)
            ui->label_tulkinta_maaritelty->setText("alipainoa");
        else if (bmi <= 26.4f && bmi > 20.7f)
            ui->label_tulkinta_maaritelty->setText("normaali");
        else if (bmi <= 27.8f && bmi > 26.4f)
            ui->label_tulkinta_maaritelty->setText("lievää ylipainoa");
        else if (bmi <= 31.1f && bmi > 27.8f)
            ui->label_tulkinta_maaritelty->setText("ylipainoa");
        else if (bmi > 31.1f)
            ui->label_tulkinta_maaritelty->setText("paljon ylipainoa");
    }
}
