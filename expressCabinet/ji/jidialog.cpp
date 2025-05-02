#include "jidialog.h"
#include "ui_jidialog.h"
#include <QDebug>
#include <QRegExpValidator>
#include "deliveryman/deliveryman.h"
jiDialog::jiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jiDialog)
{
    ui->setupUi(this);
    //ui->layoutWidget->setWindowOpacity(1.0);
    //设置编辑框只能为数字
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    connect(this,&jiDialog::sendNum,this,[=](int num){
//        qDebug()<<num<<endl;
        ui->lineEdit->insert(QString::number(num));
    });
}

jiDialog::~jiDialog()
{
    delete ui;
}
//退出按钮
void jiDialog::on_pushButtonExit_clicked()
{
    this->deleteLater();
}

void jiDialog::on_pushButton_1_clicked()
{
    emit sendNum(1);
}

void jiDialog::on_pushButton_2_clicked()
{
    emit sendNum(2);
}

void jiDialog::on_pushButton_3_clicked()
{
    emit sendNum(3);
}

void jiDialog::on_pushButton_4_clicked()
{
    emit sendNum(4);
}

void jiDialog::on_pushButton_5_clicked()
{
    emit sendNum(5);
}

void jiDialog::on_pushButton_6_clicked()
{
    emit sendNum(6);
}

void jiDialog::on_pushButton_7_clicked()
{
    emit sendNum(7);
}

void jiDialog::on_pushButton_8_clicked()
{
    emit sendNum(8);
}

void jiDialog::on_pushButton_9_clicked()
{
    emit sendNum(9);
}

void jiDialog::on_pushButton_0_clicked()
{
    emit sendNum(0);
}

void jiDialog::on_pushButtonDel_clicked()
{

    ui->lineEdit->clear();
}

void jiDialog::on_pushButtonAck_clicked()
{   
    if(ui->lineEdit->text().length() < 11 || ui->lineEdit->text().length() > 11)
    {
        QMessageBox msgBox;
        msgBox.setText("输入电话号码有误");
        msgBox.exec();
        return;
    }

    //生成一个随机数作为密码
    int num = 0;
    int passWord = (qrand() % 9000) + 1000; 
    //重新选定数据表
    QSqlTableModel tableModel;
    tableModel.setTable("expressCabinet");
    tableModel.select();

    for (int i = 0; i < tableModel.rowCount(); i++)
    {
        QModelIndex index = tableModel.index(i, 1);
        int status = tableModel.data(index).toInt();
        // 判断快递柜满了没
        bool isFull = true;
        for (int i = 0; i < tableModel.rowCount(); i++)
        {   
            QModelIndex indexTemp = tableModel.index(i, 1);
            if (tableModel.data(indexTemp).toInt() == 0)
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
            //qDebug() << QString("第%1个柜子已被占用").arg(i + 1) << endl;
            continue;
        }
        //找到未占用的柜子
        if (status == 0)
        {   /*
                打开相应的柜子
            */
            int fd = ::open("/dev/74hc138",O_RDWR);
            if(fd < 0){
                 perror("open");
                 QMessageBox::warning(this,"open","open error");
                 return;
            }
            int len = ::write(fd,&i,1);
            if(len < 0){
                 perror("write");
                 QMessageBox::warning(this,"write","open error");
                 return;
            }
            ::close(fd);
            //qDebug() << QString("第%1个柜子未被占用").arg(i + 1) << endl;
            //将柜子状态改为1
            tableModel.setData(tableModel.index(i, 1), 1);
            tableModel.setData(tableModel.index(i, 2), passWord);//四位取件码
            tableModel.setData(tableModel.index(i, 3), ui->lineEdit->text().toLongLong());//电话号码
            tableModel.submitAll();
            num = i;
            break;
        }
    }
    //最终发送的取件码
    qDebug()<<"To"<<ji::express<<"The courier sends a message with the courier pickup code:"<<num<<passWord<<"phone number:"<<ui->lineEdit->text().toLongLong()<<endl;
    

}
