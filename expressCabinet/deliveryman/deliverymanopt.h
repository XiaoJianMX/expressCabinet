#ifndef DELIVERYMANOPT_H
#define DELIVERYMANOPT_H

#include <main/mainwindow.h>
#include <QWidget>
#include <deliveryman/deliveryman.h>
namespace Ui {
class deliverymanOpt;
}

class deliverymanOpt : public QWidget
{
    Q_OBJECT

public:
    explicit deliverymanOpt(QWidget *parent = nullptr);
    ~deliverymanOpt();
    //如果一个电话号码存多个
    bool isInSave;
    void inSave();
public slots:


    void on_pushButtonExit_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonAck_clicked();

signals:
    void sendNum(int num);

private:
    Ui::deliverymanOpt *ui;
};

#endif // DELIVERYMANOPT_H
