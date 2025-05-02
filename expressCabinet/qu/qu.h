#ifndef QU_H
#define QU_H

#include <QWidget>
#include <main/mainwindow.h>
namespace Ui {
class qu;
}

class qu : public QWidget
{
    Q_OBJECT

public:
    explicit qu(QWidget *parent = nullptr);
    ~qu();
signals:
    void sendNum(int num);
private slots:
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

    void on_pushButtonExit_clicked();
signals:
    void lineEdit1HasFocus(bool isFocused);
    void lineEdit2HasFocus(bool isFocused);


     
private:
    Ui::qu *ui;
    QSqlTableModel *tableModel;

    bool lineEdit1Status;
    bool lineEdit2Status;

};

#endif // QU_H
