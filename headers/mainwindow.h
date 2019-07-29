#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"

namespace Ui {
class MainWindow;
}
class QLineEdit;
class QDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:

    void on_pushButton_EnableCAN1_clicked();

    void on_pushButton_ResertCAN1_clicked();

    void on_pushButton_EnableCAN2_clicked();

    void on_pushButton_ResertCAN2_clicked();

    void on_OpenDevice_triggered();

    void on_TestConnection_triggered();

    void on_rButton_FilterOFF_1_clicked();

    void on_rButton_FilterOFF_2_clicked();

    void on_pButton_FilterEnable_1_clicked();

    void on_pButton_FilterEnable_2_clicked();

    void on_pButton_clearData_clicked();

    void on_pButton_Send_clicked();

    void on_cBox_Receive_clicked();

    void on_pButton_Draw_clicked();

    void on_action_XML_R_triggered();

};


#endif // MAINWINDOW_H
