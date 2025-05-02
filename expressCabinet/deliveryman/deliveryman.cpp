#include "deliveryman.h"
#include "ui_deliveryman.h"
#include <QDebug>

int deliveryman::jiNum = 0;

int deliveryman::quNum = 0;

QString deliveryman::JiOrCun = NULL;

int deliveryman::IDNum = 0;

deliveryman::deliveryman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deliveryman)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignTop);
    ui->label_2->setWordWrap(true);
    ui->label_2->setAlignment(Qt::AlignTop);
    //输入界面
    
    this->setWindowFlags(Qt::FramelessWindowHint);//无标题栏   
    setAttribute(Qt::WA_TranslucentBackground,true); //设置背景透明
    //启动取件的线程
    threadqu = new threadQu;
    threadqu->start();

    //启动存件的线程
    threadji = new threadJi;
    threadji->start();


/*
    //存件的按键的信号与槽链接
    connect(ui->pushButtonSave,&QAbstractButton::clicked,this,deliveryman::on_pushButtonSave_clicked);
    //取件的按键的信号与槽链接
    connect(ui->pushButtonGet,&QAbstractButton::clicked,this,deliveryman::on_pushButtonGet_clicked);
    //退出的按键的信号与槽链接
    connect(ui->pushButtonExit,&QAbstractButton::clicked,this,deliveryman::on_pushButtonExit_clicked);

*/     

}

deliveryman::~deliveryman()
{   
    threadqu->requestInterruption();
    threadqu->exit();
    threadqu->wait();
    threadji->requestInterruption();
    threadji->exit();
    threadji->wait();
    delete threadji;
    delete threadqu;
    delete ui;
}
//取件的线程


//存件的按键的槽函数
void deliveryman::on_pushButtonSave_clicked()
{   
    //先判断柜子有没有满
    bool isFull = true;
    QSqlTableModel tableModel;
    tableModel.setTable("expressCabinet");
    tableModel.select();
    int num = 0;
    for(int i = 0; i < tableModel.rowCount(); i++)
    {   
        QModelIndex indexTemp = tableModel.index(i, 1);
        if (tableModel.data(indexTemp).toInt() == 0)
        {   
            deliveryman::IDNum = i;
            //柜子有空的，直接跳出循环，
            isFull = false;
            // qDebug()<<deliveryman::IDNum<<endl;
            break;

        }
    }
    if(isFull)
    {
        QMessageBox msgBox;
        msgBox.setText("柜子已满");
        msgBox.exec();
        return;
    }
    deliveryman::JiOrCun = "Save";
    deliverymanOpt *opt = new deliverymanOpt;
    opt->show();
}
//取件的按键的槽函数
void deliveryman::on_pushButtonGet_clicked()
{   
    deliveryman::JiOrCun = "Get";
    deliverymanOpt *opt = new deliverymanOpt;
    opt->show();
}
//退出的按键的槽函数
void deliveryman::on_pushButtonExit_clicked()
{
    this->deleteLater();
}