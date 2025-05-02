#ifndef DELIVERYMAN_H
#define DELIVERYMAN_H

#include <QThread>
#include <QWidget>
#include "ji/jidialog.h"
#include "qu/qu.h"
#include "ji/ji.h"
#include <pthread.h>
#include <QDebug>
#include "deliverymanopt.h"

class threadQu;
class threadJi;
class deliverymanopt;
namespace Ui {
class deliveryman;
}

class deliveryman : public QWidget
{
    Q_OBJECT

public:
    explicit deliveryman(QWidget *parent = nullptr);
    ~deliveryman();
    //快递员方面的寄件码和取件码

    static int quNum;
    static int jiNum;
    static int IDNum;
    static QString JiOrCun;
    static void *threadQuFunc(void *arg);
    //
public slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonGet_clicked();

    void on_pushButtonExit_clicked();



private:
    Ui::deliveryman *ui;
    threadQu *threadqu;
    threadJi *threadji;
    
};
//取件码的线程
class threadQu:public QThread
{
    Q_OBJECT

    void run()
    {
        while(!isInterruptionRequested())
        {   
            if(deliveryman::quNum > 0)
            {
                // qDebug()<<"deliveryman thread is running" <<endl;
                // qDebug()<<"确认取件码正确，做相关操作"<< deliveryman::quNum<<endl;
                deliveryman::quNum = 0;
            }
            
            QThread::msleep(100);
        }
        qDebug()<<"The thread that picks up the item exits..." <<endl;
    }
};
//寄件码码的线程
class threadJi:public QThread
{
    Q_OBJECT

    void run()
    {
        while(!isInterruptionRequested())
        {   
            if(deliveryman::jiNum > 0)
            {
                // qDebug()<<"deliveryman thread is running" <<endl;
                // qDebug()<<"确认寄件码正确，做相关操作"<< deliveryman::jiNum<<endl;
                deliveryman::jiNum = 0;
            }
            
             QThread::msleep(100);
        }
        qDebug()<<"The thread of the shipment exits..." <<endl;
    }
};
#endif // DELIVERYMAN_H
