#include "leastsquarewin.h"
#include <QPainter>
#include <QDebug>

using namespace std;

//通过最小二乘法求出 一元一次方程
class LeastSquare{
public:
    double a, b;
    LeastSquare(const vector<double>& x, const vector<double>& y)
    {
        double t1=0, t2=0, t3=0, t4=0;
        for(int i=0; i<x.size(); ++i)
        {
            t1 += x[i]*x[i];
            t2 += x[i];
            t3 += x[i]*y[i];
            t4 += y[i];
        }
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2);
        //b = (t4 - a*t2) / x.size();
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);
    }

    double getY(const double x) const
    {
        return a*x + b;
    }

    void print() const
    {
//        cout<<"a = "<<a<<"b + "<<b<<"\n";
        qDebug() << "y="<<a << " x=" << b;
    }
};


LeastSquareWin::LeastSquareWin(QWidget *parent)
    : QWidget(parent)
{
    init();
}

LeastSquareWin::~LeastSquareWin()
{

}

void LeastSquareWin::init()
{
    for (int i=0;i<100;i++) {
        if(i%5 == 0){
            mX.push_back(10*i + 80);
            mY.push_back(10*i + 3);
        }
        else{
            mX.push_back(10*i);
            mY.push_back(10*i);
        }
    }

    LeastSquare ls(mX, mY);
    ls.print();

    mA = ls.a;
    mB = ls.b;
}

//y=ax+b
void LeastSquareWin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    std::vector<double>::iterator xIter = mX.begin();
    std::vector<double>::iterator yIter = mY.begin();

    for(;xIter != mX.end();xIter++,yIter++){
        painter.drawEllipse(QPoint(*xIter,*yIter),2,2);
    }

    painter.setPen(Qt::red);

    QVector<QPointF> posList;
    for (int i=0;i<100;i++) {
        int x = i*10;
        posList.append(QPointF(x,mA*x+mB));
    }

    painter.drawPolyline(posList);
}
