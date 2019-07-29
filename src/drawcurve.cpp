#include "stdafx.h"
extern std::shared_mutex vector_mutex;
extern std::vector<VCI_CAN_OBJ> rec_vec;
#define MAX(x,y) ((x>y)?(x):(y))
widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget),
    chart(new QChart),
    timer(new QTimer),
    isStopping(false),
    x(0),
    x0(0),
    x1(10),
    ind(0),
    max_y(1)
{
    ui->setupUi(this);
    initChart();
    timer->setInterval(10);
    timer->start();
    initSlot();
}

widget::~widget()
{
    delete ui;
}


void widget::initChart()
{
    series = new QLineSeries;
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 1);
    axisY->setTitleText("Value");
    axisY->setGridLineVisible(false);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAxisY(axisY, series);
    chart->axisX()->setRange(0,10);
    chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart->axisX()->setTitleText("Time/sec");
    chart->axisX()->setGridLineVisible(false);
    /* hide legend */
    chart->legend()->hide();
    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->mainHorLayout->addWidget(chartView);
}

void widget::initSlot()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    connect(ui->stopBtn, SIGNAL(clicked(bool)), this, SLOT(buttonSlot()));
}

void widget::updateData(SignalFormat &cell)
{

    QVector<QPointF> oldData = series->pointsVector();

    if(rec_vec.size()>0&&ind<rec_vec.size())
    {
        auto val= cell.DataUnit(rec_vec[ind]);
        if (oldData.size() < 1000)
        {
            oldData.append(QPointF(x, val));
        }
        else
        {
            chart->axisX()->setRange(x0+=0.01,x1+=0.01);
            oldData.pop_front();
            oldData.append(QPointF(x, val));
        }
        series->replace(oldData);
        chart->axisY()->setRange(0,MAX(max_y,val));
        if(max_y<val)
            max_y=val;
        ind++;
        x+=0.01;
    }
    else if(rec_vec.size()>0&&ind==rec_vec.size())
    {
        auto val= cell.DataUnit(rec_vec[ind-1]);
        if (oldData.size() < 1000)
        {
            oldData.append(QPointF(x, val));
        }
        else
        {
            chart->axisX()->setRange(x0+=0.01,x1+=0.01);
            oldData.pop_front();
            oldData.append(QPointF(x, val));
        }
        series->replace(oldData);
        x+=0.01;
    }
    else
    {
        if (oldData.size() < 1000)
        {
            oldData.append(QPointF(x, 0));//0对应数据点
        }
        else
        {
            chart->axisX()->setRange(x0+=0.01,x1+=0.01);
            oldData.pop_front();
            oldData.append(QPointF(x, 0));//0对应数据点
        }
        series->replace(oldData);
        x+=0.01;
    }

}

void widget::timerSlot()
{   extern std::map<std::string,SignalFormat> RuleMap;
    SignalFormat cell;
    std::string name= SignalName.QString::toStdString();
    if(RuleMap.find(name)!=RuleMap.end())
    {
        std::map<std::string,SignalFormat>::iterator iter=RuleMap.find(name);
        cell=iter->second;
    }
    if (QObject::sender() == timer) {
        updateData(cell);
    }
}

void widget::buttonSlot()
{
    if (QObject::sender() == ui->stopBtn) {
        if (!isStopping) {
            timer->stop();
        } else {
            timer->start();
        }
        isStopping = !isStopping;
    }
}

