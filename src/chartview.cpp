#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    isClicking(false),
    xOld(0), yOld(0)
{
    setRubberBand(QChartView::RectangleRubberBand);
}
