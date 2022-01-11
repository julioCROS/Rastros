#include "Rastros.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rastros w;
    w.show();
    return a.exec();
}
