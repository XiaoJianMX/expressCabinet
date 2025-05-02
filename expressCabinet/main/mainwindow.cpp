#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qu/qu.h"
#include <QDebug>
#include <QDate>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 显示日期
    ui->lcdNumber->setOctMode();
    ui->lcdNumber->setDigitCount(10);
    ui->lcdNumber->display(QDate::currentDate().toString("yyyy-MM-dd"));
    // 设置sqltable
    tableModel = new QSqlTableModel;
    tableModel->setTable("expressCabinet");
    tableModel->select();
}

MainWindow::~MainWindow()
{
    delete tableModel;
    delete ui;
}

// 寄件的按键
void MainWindow::on_pushButtonShip_clicked()
{
    // 判断快递柜有没有满
    tableModel->setTable("expressCabinet");
    tableModel->select();
    bool isFull = true;
    for (int i = 0; i < tableModel->rowCount(); i++)
    {
        QModelIndex indexTemp = tableModel->index(i, 1);
        if (tableModel->data(indexTemp).toInt() == 0)
        {
            isFull = false;
        }
    }
    // 满了的话就返回并且提示
    if (isFull)
    {
        QMessageBox msgBox;
        msgBox.setText("快递柜已满！！");
        msgBox.exec();
        return;
    }
    ji *j = new ji;
    j->show();
    qDebug() << "on_pushButtonShip_clicked" << endl;
}
// 取件的按键
void MainWindow::on_pushButtonCollect_clicked()
{
    qu *q = new qu;
    q->show();
}
// 快递员的按键
void MainWindow::on_pushButtonDeliveryman_clicked()
{
    deliveryman *d = new deliveryman;
    d->show();
}
// 寄存的按键
void MainWindow::on_pushButtonCheck_clicked()
{   

    //生成一个随机数作为密码
    int num = 0;
    int passWord = (qrand() % 9000) + 1000; 
    //重新选定数据表
    tableModel->setTable("expressCabinet");
    tableModel->select();

    for (int i = 0; i < tableModel->rowCount(); i++)
    {
        QModelIndex index = tableModel->index(i, 1);
        int status = tableModel->data(index).toInt();
        // 判断快递柜满了没
        bool isFull = true;
        for (int i = 0; i < tableModel->rowCount(); i++)
        {   
            QModelIndex indexTemp = tableModel->index(i, 1);
            if (tableModel->data(indexTemp).toInt() == 0)
            {
                isFull = false;
            }
        }
        //满了的话就返回并且提示
        if (isFull)
        {
            QMessageBox msgBox;
            msgBox.setText("快递柜已满！！");
            msgBox.exec();
            return;
        }
        //如果柜子被占用，直接跳过循环
        if (status == 1)
        {
            continue;
        }
        //找到未占用的柜子
        if (status == 0)
        {
            tableModel->setFilter(QString("id=%1").arg(i));
            tableModel->select();
            QSqlRecord record = tableModel->record(0);
            record.setValue("status", 1);
            record.setValue("password", passWord);
            tableModel->setRecord(0, record);
            tableModel->submitAll();
            tableModel->setTable("expressCabinet");
            tableModel->select();
            num = i;
            break;
        }
    }
    QMessageBox messageBox;
    messageBox.setText(QString("你的取件码为%1-%2").arg(num).arg(passWord));
    messageBox.exec();
    //最终发送的取件码
    qDebug()<<"Your pickup code:"<<num<<"-"<<passWord<<endl;
}
