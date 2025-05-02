#include "qu.h"
#include "ui_qu.h"
#include <QDebug>

#include "deliveryman/deliveryman.h"
qu::qu(QWidget *parent) : QWidget(parent),
                          ui(new Ui::qu)
{
    ui->setupUi(this);

    tableModel = new QSqlTableModel;
    // 选中编辑框1
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, [=]()
            {
        this->lineEdit1Status = true;
        this->lineEdit2Status = false; });
    // 选中编辑框2
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, [=]()
            {
        this->lineEdit2Status = true;
        this->lineEdit1Status = false; });
    connect(this, &qu::sendNum, this, [=](int num)
            {
        if(lineEdit1Status)
            ui->lineEdit->insert(QString::number(num)); });
    connect(this, &qu::sendNum, this, [=](int num)
            {
        if(lineEdit2Status)
            ui->lineEdit_2->insert(QString::number(num)); });
}

qu::~qu()
{
    delete tableModel;
    delete ui;
}

void qu::on_pushButton_1_clicked()
{
    emit sendNum(1);
}

void qu::on_pushButton_2_clicked()
{
    emit sendNum(2);
}

void qu::on_pushButton_3_clicked()
{
    emit sendNum(3);
}

void qu::on_pushButton_4_clicked()
{
    emit sendNum(4);
}

void qu::on_pushButton_5_clicked()
{
    emit sendNum(5);
}

void qu::on_pushButton_6_clicked()
{
    emit sendNum(6);
}

void qu::on_pushButton_7_clicked()
{
    emit sendNum(7);
}

void qu::on_pushButton_8_clicked()
{
    emit sendNum(8);
}

void qu::on_pushButton_9_clicked()
{
    emit sendNum(9);
}

void qu::on_pushButton_0_clicked()
{
    emit sendNum(0);
}

void qu::on_pushButtonDel_clicked()
{
    if (lineEdit1Status)
        ui->lineEdit->clear();
    else
        ui->lineEdit_2->clear();
}

void qu::on_pushButtonAck_clicked()
{
    QMessageBox msgBox;
    msgBox.setBaseSize(300, 400);
    msgBox.resize(300, 400);

    // 判断取件码的对错
    if (ui->lineEdit->text().toInt() > 9 || ui->lineEdit->text().toInt() < 0)
    {

        msgBox.setText("输入取件码有误.");
        msgBox.exec();
        return;
    }
    // 判断取件的密码是否正确
    tableModel->setTable("expressCabinet");
    tableModel->select();
    QModelIndex passWordIndex = tableModel->index(ui->lineEdit->text().toInt(), 2);
    int tempPassWord = tableModel->data(passWordIndex).toInt();
    // 不正确则直接return
    if (ui->lineEdit_2->text().toInt() != tempPassWord)
    {
        msgBox.setText("输入取件码有误或者已被取走");
        msgBox.exec();
        return;
    }
    // 遍历数据库，找到取ID为ui->lineEdit->text().toUInt()的柜子
    tableModel->setTable("expressCabinet");
    tableModel->select();
    QModelIndex IDindex = tableModel->index(ui->lineEdit->text().toInt(), 1);
    int status = tableModel->data(IDindex).toInt();
    if (status == 1)
    {
         int fd = ::open("/dev/74hc138", O_RDWR);
         if (fd < 0)
         {
             perror("open");
             QMessageBox::warning(this, "open", "open error");
             return;
         }
         int i = ui->lineEdit->text().toInt();
         int len = ::write(fd, &i, 1);
         if (len < 0)
         {
             perror("write");
             QMessageBox::warning(this, "write", "open error");
             return;
         }
         ::close(fd);
        // 取走物品后 将数据库中的status改为0 密码改为0
        tableModel->setData(IDindex, 0);
        tableModel->setData(passWordIndex, 0);
        tableModel->setData(tableModel->index(ui->lineEdit->text().toInt(), 3), 0);
        tableModel->submitAll();
        msgBox.setText("取件成功，请尽快取出您的物品");
        msgBox.exec();
        // qDebug()<<"取件码为："<<ui->lineEdit->text().toInt()<<"打开，取走物品"<<endl;
    }
}

void qu::on_pushButtonExit_clicked()
{
    this->deleteLater();
}
