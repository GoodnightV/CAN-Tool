#include "stdafx.h"
#include "mainwindow.h"
#pragma execution_character_set("utf-8")
/*Some Global Variables*/
QT_CHARTS_USE_NAMESPACE
VCI_BOARD_INFO pInfo;
VCI_INIT_CONFIG config;
std::map<std::string,SignalFormat> RuleMap;
std::vector<VCI_CAN_OBJ> rec_vec;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_EnableCAN1_clicked()
{
    QMessageBox InitFaultBox;
    InitFaultBox.setWindowTitle("提示");
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
    config.Filter=1;//接收所有帧
    config.Timing0=0x00;/*波特率500 Kbps  0x00  0x1C*/
    config.Timing1=0x1C;
    config.Mode=0;//正常模式
    if(VCI_InitCAN(VCI_USBCAN2,0,0,&config)==1&&VCI_StartCAN(VCI_USBCAN2,0,0)==1)
    {
        InitFaultBox.setText("通道1初始化成功，波特率为500Kbps，接受所有帧");
        InitFaultBox.exec();
    }
    else
    {
        InitFaultBox.setText("打开通道1失败，请重试或检查设备！");
        InitFaultBox.exec();
        VCI_CloseDevice(VCI_USBCAN2,0);
    }

}

void MainWindow::on_pushButton_ResertCAN1_clicked()
{

    QMessageBox InitFaultBox;//将CAN1复位原始设置
    InitFaultBox.setWindowTitle("提示");
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
    config.Filter=1;//接收所有帧
    config.Timing0=0x00;/*波特率500 Kbps  0x00  0x1C*/
    config.Timing1=0x1C;
    config.Mode=0;//正常模式
    if(VCI_ResetCAN(VCI_USBCAN2, 0, 0)==1)
    {
        InitFaultBox.setText("已复位默认设置");
        InitFaultBox.exec();
    }
    else
    {
        InitFaultBox.setText("复位通道1失败，请重试或检查设备！");
        InitFaultBox.exec();
        VCI_CloseDevice(VCI_USBCAN2,0);
    }
}

void MainWindow::on_pushButton_EnableCAN2_clicked()
{
    QMessageBox InitFaultBox;
    InitFaultBox.setWindowTitle("提示");
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
    config.Filter=1;//接收所有帧
    config.Timing0=0x00;/*波特率500 Kbps  0x00  0x1C*/
    config.Timing1=0x1C;
    config.Mode=0;//正常模式
    if(VCI_InitCAN(VCI_USBCAN2,0,1,&config)==1&&VCI_StartCAN(VCI_USBCAN2,0,1)==1)
    {

        InitFaultBox.setText("通道2初始化成功，波特率为500Kbps，接受所有帧");
        InitFaultBox.exec();
    }
    else
    {
        InitFaultBox.setText("打开通道2失败，请重试或检查设备！");
        InitFaultBox.exec();
        VCI_CloseDevice(VCI_USBCAN2,0);
    }
}

void MainWindow::on_pushButton_ResertCAN2_clicked()
{
    QMessageBox InitFaultBox;//将CAN2复位原始设置
    InitFaultBox.setWindowTitle("提示");
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
    config.Filter=1;//接收所有帧
    config.Timing0=0x00;/*波特率500 Kbps  0x00  0x1C*/
    config.Timing1=0x1C;
    config.Mode=0;//正常模式
    if(VCI_ResetCAN(VCI_USBCAN2, 0, 1)==1)
    {
        InitFaultBox.setText("已复位默认设置");
        InitFaultBox.exec();
    }
    else
    {
        InitFaultBox.setText("复位通道2失败，请重试或检查设备！");
        InitFaultBox.exec();
        VCI_CloseDevice(VCI_USBCAN2,0);
    }
}



void MainWindow::on_OpenDevice_triggered()
{
    if(VCI_OpenDevice(VCI_USBCAN2,0,0)==1)//打开设备
    {
       if(VCI_ReadBoardInfo(VCI_USBCAN2,0,&pInfo)==1)
       {
            QMessageBox msgBox;
            msgBox.setWindowTitle("提示");
            QString SerialNum(pInfo.str_Serial_Num);
            QString HardwareType(pInfo.str_hw_Type);
            msgBox.setText("设备已经打开，序列号为:"+SerialNum+"  硬件版本为:"+HardwareType);
            msgBox.exec();
       }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("打开失败，请重试！");
        msgBox.exec();
    }
}

void MainWindow::on_TestConnection_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("连接状态");

    if(VCI_ConnectDevice(VCI_USBCAN2,0)==1)
    {
        msgBox.setText("正常通信");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("设备已掉线");
        msgBox.exec();
    }
}

void MainWindow::on_rButton_FilterOFF_1_clicked()
{
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
}
void MainWindow::on_rButton_FilterOFF_2_clicked()
{
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
}

void MainWindow::on_pButton_FilterEnable_1_clicked()
{
    if(!(ui->rButton_FilterON_1->isChecked()))
    {
        QMessageBox box;
        box.setText("请先打开滤波！");
        box.setWindowTitle("警告");
        box.exec();
        return;
    }
    else
    {
        std::vector<QString> filterID_1;
        auto temp=ui->lineEdit_FilterID_1->text();
        std::stringstream str;
        str << (temp.toStdString());
        std::string mid;
        while (str >> mid)
            filterID_1.push_back(QString::fromStdString(mid));
    }
}

void MainWindow::on_pButton_FilterEnable_2_clicked()
{
    if(!(ui->rButton_FilterON_2->isChecked()))
    {
        QMessageBox box;
        box.setText("请先打开滤波！");
        box.setWindowTitle("警告");
        box.exec();
        return;
    }
    else
    {
        std::vector<QString> filterID_2;
        auto temp=ui->lineEdit_FilterID_2->text();
        std::stringstream str;
        str << (temp.toStdString());
        std::string mid;
        while (str >> mid)
            filterID_2.push_back(QString::fromStdString(mid));
    }
}

void MainWindow::on_pButton_clearData_clicked()
{
    ui->tWidget_DataVisualize->clearContents();
    ui->tWidget_DataVisualize->setRowCount(0);
}

void MainWindow::on_pButton_Send_clicked()
{
    VCI_CAN_OBJ send[1];
    send[0].RemoteFlag=0;
    send[0].ExternFlag=1;
    send[0].DataLen=8;
    if(ui->lineEdit_FrameID->text()!="")
        send[0].ID=stoi(ui->lineEdit_FrameID->text().toStdString(),nullptr,16);
    else
        send[0].ID=0;
    send[0].SendType=0;
    if(ui->cBox_FrameStandard->currentText()=="标准帧")
        send[0].ExternFlag=0;
    else
        send[0].ExternFlag=1;
    if(ui->cBox_FrameType->currentText()=="数据帧")
        send[0].RemoteFlag=0;
    else
        send[0].RemoteFlag=1;

    QString data=ui->lineEdit_DataSend->text();
    std::stringstream str;
    str << (data.toStdString());
    std::string mid;
    std::vector<QString> temp;
    while (str >> mid)
        temp.push_back(QString::fromStdString(mid));
    send[0].DataLen=temp.size();
    for(int i=0;i<send[0].DataLen;i++)
    {
        BYTE x=temp[i].toInt(nullptr,16);
        send[0].Data[i]= x;
    }
    if(VCI_Transmit(VCI_USBCAN2, 0, ui->cBox_CANSelect->currentIndex(), send, 1)==1)
    {
        InsertItem(ui,send[0],"Tx",QString::number(ui->cBox_CANSelect->currentIndex()+1));
    }
}
void MainWindow::on_cBox_Receive_clicked()
{   if(ui->cBox_Receive->isChecked())
    {
        std::thread t(receive_func,ui);
        t.detach();
    }
}
void MainWindow::on_pButton_Draw_clicked()
{   /*QString data=ui->lineEdit_DrawID->text();
    std::stringstream str;
    str << (data.toStdString());
    std::string mid;
    std::vector<QString> ID;
    while (str >> mid)
        ID.push_back(QString::fromStdString(mid));
    if(ID.size()==0)
    {
        QMessageBox box;
        box.setText("无曲线分析ID");
        box.setWindowTitle("提示");
        box.exec();
    }
    else
    {*/
    {
        widget *ptr=new widget;
        ptr->setWindowTitle("实时分析："+ui->cBox_SigName->currentText());
        QString SigName=ui->cBox_SigName->currentText();
        ptr->setName(SigName);
        ptr->show();
    }
}

void MainWindow::on_action_XML_R_triggered()
{
    static std::set<std::string> s;
    QString XMLfileName = QFileDialog::getOpenFileName(this, tr("打开XML文件"), " ",  tr("Allfile(*.*);;XMLfile(*.xml)"));
    QStringList args;
    args.append(QApplication::applicationDirPath()+"/XML.py");
    args.append(XMLfileName);
    QProcess::execute(QString("Python.exe"), args);
    QString path=QApplication::applicationDirPath()+"/log.txt";
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"Open Failed"<<std::endl;
    }
    QTextStream is(&f);
    QString line;
    while(!is.atEnd())
    {
        line=is.readLine();
        qDebug()<<line;
        std::stringstream str;
        str << line.toStdString();
        std::string name;
        std::string ID;
        std::string byte;
        std::string bit;
        std::string pos;
        str>>name>>ID>>byte>>bit>>pos;
        SignalFormat text(QString::fromStdString(name),QString::fromStdString(ID).toULong(NULL,16),
                         QString::fromStdString(byte).toUInt(),
                          QString::fromStdString(bit).toUInt(),
                          QString::fromStdString(pos).toUInt());
        RuleMap.insert({name,text});
        if(std::find(s.begin(),s.end(),name)==s.end())
        {
            s.insert(name);
            ui->cBox_SigName->addItem(text.name);
        }
    }

}
