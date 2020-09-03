#ifndef LEASTSQUAREWIN_H
#define LEASTSQUAREWIN_H

#include <QWidget>

class LeastSquareWin : public QWidget
{
    Q_OBJECT

public:
    LeastSquareWin(QWidget *parent = nullptr);
    ~LeastSquareWin();

    void init();

private:
    void paintEvent(QPaintEvent *event);

    std::vector<double> mX,mY;
    double mA,mB;

    std::list<int> findPeaks( const std::vector<double> &amp );

};
#endif // LEASTSQUAREWIN_H
