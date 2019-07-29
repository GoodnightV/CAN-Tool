#ifndef CONFIG_FUNC_H
#define CONFIG_FUNC_H

#include "stdafx.h"


void InsertItem(Ui::MainWindow* ui,VCI_CAN_OBJ send,QString via,QString pass);
QString Convert(unsigned int ID);
class SignalFormat
{
public:
    SignalFormat() = default;
    SignalFormat(QString _name,unsigned long ID, unsigned int byte, unsigned int pos, unsigned int bit) :
        name(_name),ID(ID), byte(byte), pos(pos), bit(bit) {}
    unsigned long long DataUnit(VCI_CAN_OBJ&);
    unsigned long getID()const{return ID;}
    QString name;
private:
    unsigned long ID;
    unsigned int byte;
    unsigned int pos;
    unsigned int bit;
};



#endif // CONFIG_FUNC_H
