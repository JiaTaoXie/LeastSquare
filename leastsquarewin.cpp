#include "leastsquarewin.h"
#include <QPainter>
#include <QDebug>

using namespace std;

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

    std::pair<double,double> data = caclLeastSquare(mX,mY);
    mA = data.first;
    mB = data.second;

    LeastSquare ls(mX, mY);
    ls.print();

    qDebug() << "ma:" << mA << " mb:" << mB;

//    mA = ls.a;
//    mB = ls.b;
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

std::list<int> LeastSquareWin::findPeaks( const std::vector<double> &amp )
{
   const double NOISE = -1;               // Level up to and including which peaks will be excluded
   int wideStart = -1;                 // The start of any current wide peak

   int grad = -1;                      // Sign of gradient (almost)
                                       //    =  1 for increasing
                                       //    =  0 for level AND PREVIOUSLY INCREASING (so potential wide peak)
                                       //    = -1 for decreasing OR level, but previously decreasing
                                       // A sharp peak is identified by grad=1 -> grad=-1
                                       // A wide  peak is identified by grad=0 -> grad=-1

   std::list<int> peakIndexList;

   for ( int i = 0; i < amp.size() - 1; i++ )
   {
      if ( amp[i+1] < amp[i] )         // Only possibility of a peak
      {
         if ( grad == 1 && amp[i] > NOISE )
         {
//            cout << "Sharp peak of " << amp[i] << " at i = " << i << '\n';
            peakIndexList.push_back(i);
         }
         else if ( grad == 0 && amp[i] > NOISE )
         {
//            cout << "Wide peak of " << amp[i] << " from i = " << wideStart << " to " << i << '\n';
            peakIndexList.push_back(i);
         }
         grad = -1;
      }
      else if ( amp[i+1] == amp[i] )   // Check for start of a wide peak
      {
         if ( grad == 1 )
         {
            wideStart = i;
            grad = 0;
         }
      }
      else
      {
         grad = 1;
      }
   }
   qDebug() << "peakIndexList:" << peakIndexList;
   return peakIndexList;
}

std::pair<double,double> LeastSquareWin::caclLeastSquare(const vector<double>& x, const vector<double>& y)
{
    double a,b;
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

    return std::pair<double,double>(a,b);
}
