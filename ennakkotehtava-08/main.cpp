#include "paaikkuna.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Paaikkuna w;
    w.show();

    return a.exec();
}
