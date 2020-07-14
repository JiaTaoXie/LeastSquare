#include "leastsquarewin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeastSquareWin w;
    w.show();
    return a.exec();
}
