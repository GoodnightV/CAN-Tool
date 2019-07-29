#include "stdafx.h"
extern std::shared_mutex vector_mutex;
extern std::vector<VCI_CAN_OBJ> rec_vec;
void receive_func(Ui::MainWindow* ui)  //接收线程。
{
    VCI_CAN_OBJ rec[3000];//接收缓存，设为3000为佳。
    int reclen=0;
    int ind=0;
    while(ui->cBox_Receive->isChecked()==true)
    {   int times=0;
        std::unique_lock<std::shared_mutex> writerLock(vector_mutex);
        if((reclen=VCI_Receive(VCI_USBCAN2,0,ind,rec,3000,30))>0)//调用接收函数，如果有数据，进行数据处理显示。
        {
            for(int i=0;i<reclen;i++)
            {
                InsertItem(ui,rec[times+i],"Rx",QString::number(ind+1));
                rec_vec.push_back(rec[i]);
            }
            times+=reclen;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        ind=!ind;//变换通道号，以便下次读取另一通道，交替读取。
    }
}
