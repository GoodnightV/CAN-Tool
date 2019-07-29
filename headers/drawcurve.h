#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include "chartview.h"
#include "stdafx.h"
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class widget;
}
class SignalFormat;
class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    ~widget();
    void setName(QString SigName){SignalName=SigName;}
   unsigned int  max_y;
    unsigned int ind;
private:
    Ui::widget *ui;
    void initUI();
    void initChart();
    void initSlot();
    void updateData(SignalFormat&);

    ChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QTimer *timer;
    QString SignalName;
    double x;
    double x0;
    double x1;
    bool isStopping;
    std::vector<VCI_CAN_OBJ> vec;
private slots:
    void timerSlot();
    void buttonSlot();
};

#endif // WIDGET_H
