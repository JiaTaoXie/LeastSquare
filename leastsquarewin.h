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
    std::pair<double,double> caclLeastSquare(const std::vector<double>& x, const std::vector<double>& y);

};
#endif // LEASTSQUAREWIN_H
