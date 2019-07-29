#include "stdafx.h"
#pragma execution_character_set("utf-8")
std::shared_mutex vector_mutex;


int main(int argc, char *argv[])
{   QApplication a(argc, argv);
    MainWindow w;
    /*Table Initializing*/
    w.ui->tWidget_DataVisualize->resizeColumnsToContents();
    w.ui->tWidget_DataVisualize->resizeRowsToContents();
    w.ui->tWidget_DataVisualize->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*Table Initializing*/

    w.show();
    w.setWindowTitle(QObject::tr("测试工具 by Raymond"));
    return a.exec();
}
