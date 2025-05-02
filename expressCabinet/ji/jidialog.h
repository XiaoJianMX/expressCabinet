#ifndef JIDIALOG_H
#define JIDIALOG_H

#include <QDialog>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <unistd.h>
#include "ji.h"
namespace Ui {
class jiDialog;
}

class jiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit jiDialog(QWidget *parent = nullptr);
    ~jiDialog();

private slots:
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
    Ui::jiDialog *ui;
};

#endif // JIDIALOG_H
