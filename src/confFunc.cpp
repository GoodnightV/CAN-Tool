#include "stdafx.h"
#pragma execution_character_set("utf-8")
using namespace  std;
QString Convert(unsigned int ID)
{
    QString ret;
    stack<char> s;
    while (ID != 0)
    {
        if (ID % 16 < 10)
            s.push((ID % 16) + '0');
        else
            s.push((ID % 16) + 'A'-10);
        ID = ID / 16;
    }
    while (!s.empty())
    {
        ret.push_back(s.top());
        s.pop();
    }
    return ret;
}
void InsertItem(Ui::MainWindow* ui,VCI_CAN_OBJ send,QString via,QString pass)
{
    int index=ui->tWidget_DataVisualize->rowCount();
    ui->tWidget_DataVisualize->setRowCount(index+1);
    ui->tWidget_DataVisualize->setItem(index,0,new QTableWidgetItem("CAN"+pass));
    ui->tWidget_DataVisualize->setItem(index,1,new QTableWidgetItem(via));
    QString ID="0x"+Convert(send.ID);
    ui->tWidget_DataVisualize->setItem(index,2,new QTableWidgetItem(ID));
    if(send.ExternFlag==0)
        ui->tWidget_DataVisualize->setItem(index,3,new QTableWidgetItem("标准帧"));
    else
        ui->tWidget_DataVisualize->setItem(index,3,new QTableWidgetItem("扩展帧"));
    if(send.RemoteFlag==0)
        ui->tWidget_DataVisualize->setItem(index,4,new QTableWidgetItem("数据帧"));
    else
        ui->tWidget_DataVisualize->setItem(index,4,new QTableWidgetItem("远程帧"));
    ui->tWidget_DataVisualize->setItem(index,5,new QTableWidgetItem(QString::number(send.DataLen)));
    QString data;
    for(int i=0;i<send.DataLen;++i)
    {
        if(QString::number(send.Data[i],16).size()<2)
            data+="0"+QString::number(send.Data[i])+" ";
        else
            data+=QString::number(send.Data[i],16).toUpper()+" ";
    }

    ui->tWidget_DataVisualize->setItem(index,6,new QTableWidgetItem(data));
    ui->tWidget_DataVisualize->resizeColumnsToContents();
    ui->tWidget_DataVisualize->resizeRowsToContents();
}
unsigned long long SignalFormat::DataUnit(VCI_CAN_OBJ& OBJ)
{
    unsigned char data_byte = OBJ.Data[byte];
    unsigned long long sum = 0;
    data_byte=data_byte>>pos;
    switch(bit)
    {
        case 0:
            sum=data_byte&0b00000000;
            break;
        case 1:
            sum=data_byte&0b00000001;
            break;
        case 2:
            sum=data_byte&0b00000011;
            break;
        case 3:
            sum=data_byte&0b00000111;
            break;
        case 4:
            sum=data_byte&0b00001111;
            break;
        case 5:
            sum=data_byte&0b00011111;
            break;
        case 6:
            sum=data_byte&0b00111111;
            break;
        case 7:
            sum=data_byte&0b01111111;
            break;
        case 8:
            sum=data_byte&0b11111111;
            break;
    }
    return sum;
}

