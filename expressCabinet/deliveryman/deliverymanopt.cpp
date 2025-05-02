#include "deliverymanopt.h"
#include "ui_deliverymanopt.h"

deliverymanOpt::deliverymanOpt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deliverymanOpt)
{
    ui->setupUi(this);
    //将数字按键显示在lineEdit
    connect(this,&deliverymanOpt::sendNum,this,[=](int num){
        ui->lineEdit->insert(QString::number(num));
    });

    isInSave = false;

}

deliverymanOpt::~deliverymanOpt()
{
    delete ui;
}

void deliverymanOpt::inSave()
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
            break;

        }
    }
    if(isFull)
    {   
        isInSave = true;
        QMessageBox msgBox;
        msgBox.setText("柜子已满");
        msgBox.exec();
        return;
    }
}

void deliverymanOpt::on_pushButtonExit_clicked()
{
    this->hide();
}


void deliverymanOpt::on_pushButton_1_clicked()
{
    emit sendNum(1);
}

void deliverymanOpt::on_pushButton_2_clicked()
{
    emit sendNum(2);
}

void deliverymanOpt::on_pushButton_3_clicked()
{
    emit sendNum(3);
}

void deliverymanOpt::on_pushButton_4_clicked()
{
    emit sendNum(4);
}

void deliverymanOpt::on_pushButton_5_clicked()
{
    emit sendNum(5);
}

void deliverymanOpt::on_pushButton_6_clicked()
{
    emit sendNum(6);
}

void deliverymanOpt::on_pushButton_7_clicked()
{
    emit sendNum(7);
}

void deliverymanOpt::on_pushButton_8_clicked()
{
    emit sendNum(8);
}

void deliverymanOpt::on_pushButton_9_clicked()
{
    emit sendNum(9);
}

void deliverymanOpt::on_pushButton_0_clicked()
{
    emit sendNum(0);
}

void deliverymanOpt::on_pushButtonDel_clicked()
{

    ui->lineEdit->clear();
}

void deliverymanOpt::on_pushButtonAck_clicked()
{   
    //判断电话是否正确
    if(ui->lineEdit->text().length() <11 || ui->lineEdit->text().length() > 11)
    {
        QMessageBox msgBox;
        msgBox.setText("请输入11位电话号码");
        msgBox.exec();
        return;
    }
    //随机数密码
    int passWord = (qrand() % 9000) + 1000; 
    if(deliveryman::JiOrCun == "Save"){//快递员存件
        this->inSave();
        if(isInSave) return;
        QSqlTableModel tableModel;
        tableModel.setTable("expressCabinet");
        tableModel.select();
        tableModel.setData(tableModel.index(deliveryman::IDNum, 1), 1);
        tableModel.setData(tableModel.index(deliveryman::IDNum, 2), passWord);
        tableModel.setData(tableModel.index(deliveryman::IDNum, 3), ui->lineEdit->text().toLongLong());
        tableModel.submitAll();
        qDebug()<<"To the user:"<<ui->lineEdit->text().toLongLong()<<"Send a pickup code:"<<deliveryman::IDNum<<passWord<<endl;
        //提示柜子打开，尽快存件
        QMessageBox msgBox;
        msgBox.setText("柜子已打开，请存件");
        msgBox.exec();
    }else if(deliveryman::JiOrCun == "Get"){//快递员取件
        int num = 0;//总共有几件物品 
        QSqlTableModel tableModel;
        tableModel.setTable("expressCabinet");
        tableModel.select();
        //遍历数据库，找到电话号码相匹配的
        for(int i = 0; i < tableModel.rowCount(); i++)
        {
            QModelIndex index = tableModel.index(i, 3);
            if(tableModel.data(index).toLongLong() == ui->lineEdit->text().toLongLong()){
                //取走物品后 将数据库中的status改为0 密码改为0， 电话号码改为0
                tableModel.setData(tableModel.index(i, 1), 0);
                tableModel.setData(tableModel.index(i, 2), 0);
                tableModel.setData(tableModel.index(i, 3), 0);
                num++;
                //打开柜子的操作
                tableModel.submitAll();
            }
        }
        if(num == 0){
            QMessageBox msgBox;
            msgBox.setText("没有找到您的物品");
            msgBox.exec();
            return;
        }else{
            QMessageBox msgBox;
            msgBox.setText(QString("一共有%1件物品，请去走").arg(num));
            msgBox.exec();
        }
        
    }
    

}