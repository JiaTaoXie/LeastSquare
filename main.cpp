#include "leastsquarewin.h"

#include <QApplication>

/*
    通过最小二乘法求出 一元一次方程
    若应用在k线中，则线将一个区域里的k线排序找出最小的几个值3-5，再将这几个点以此进行最小二乘法（2个点，3个点，4个点），
    将得到的几条直线重新最小二乘法
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeastSquareWin w;
    w.show();
    return a.exec();
}
