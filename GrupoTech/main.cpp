#include "impresora.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Impresora w;
    w.show();
    return a.exec();
}
