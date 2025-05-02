#include "ji.h"
#include "ui_ji.h"

QString ji::deliveryman = NULL;
QString ji::express = NULL;
ji::ji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ji)
{
    ui->setupUi(this);
    
}

ji::~ji()
{
    delete ui;
}

void ji::on_pushButtonExit_clicked()
{
    this->deleteLater();
}
//京东快递
void ji::on_pushButton_2_clicked()
{
    ji::express = "jingdong";
    jiDialog *dialog  = new jiDialog;
    dialog->show();
}
//顺丰快递
void ji::on_pushButton_4_clicked()
{
    ji::express = "shunfeng";
    jiDialog *dialog  = new jiDialog;
    dialog->show();
}
//圆通快递
void ji::on_pushButton_3_clicked()
{
    ji::express = "yuantong";
    jiDialog *dialog  = new jiDialog;
    dialog->show();
}
//韵达快递
void ji::on_pushButton_5_clicked()
{
    ji::express = "yunda";
    jiDialog *dialog  = new jiDialog;
    dialog->show();
}
