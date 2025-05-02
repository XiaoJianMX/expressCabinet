#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRecord>
#include "ji/ji.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include "deliveryman/deliveryman.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonShip_clicked();

    void on_pushButtonCollect_clicked();

    void on_pushButtonDeliveryman_clicked();

    void on_pushButtonCheck_clicked();
private:
    Ui::MainWindow *ui;
    QSqlTableModel *tableModel;
};
#endif // MAINWINDOW_H
