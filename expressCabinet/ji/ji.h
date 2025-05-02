#ifndef JI_H
#define JI_H

#include <QWidget>
#include "ji/jidialog.h"
namespace Ui {
class ji;
}

class ji : public QWidget
{
    Q_OBJECT

public:
    explicit ji(QWidget *parent = nullptr);
    ~ji();


    static QString deliveryman;
    static QString express;
private slots:
    void on_pushButtonExit_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ji *ui;

};

#endif // JI_H
