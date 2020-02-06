#include "paaikkuna.hh"
#include "ui_paaikkuna.h"

Paaikkuna::Paaikkuna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);
    this->setWindowTitle("km/h -> mailia/h");
    this->setMinimumSize(400,140);
    this->setMaximumSize(400,140);
    connect(ui->pushButton_nollaa, SIGNAL(clicked()),
            this, SLOT(nollaa_kaikki_arvot()));
    connect(ui->spinBox_kmh, SIGNAL(valueChanged(int)),
            this, SLOT(laske_mailia_tunnissa()));
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::nollaa_kaikki_arvot()
{
    ui->spinBox_kmh->setValue(0);
    ui->horizontalSlider_kmh->setValue(0);
    ui->lcdNumber_mailiah->display(0.0);
}

void Paaikkuna::laske_mailia_tunnissa()
{
    double mailia_tunnissa = ui->spinBox_kmh->value() / 1.609344;
    ui->lcdNumber_mailiah->display(mailia_tunnissa);
}
