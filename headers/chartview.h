#ifndef __CHARTVIEW_H__
#define __CHARTVIEW_H__

#include <QChartView>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QChart *chart, QWidget *parent = 0);

protected:
private:
    bool isClicking;
    int xOld;
    int yOld;

};

#endif /* __CHARTVIEW_H__ */
