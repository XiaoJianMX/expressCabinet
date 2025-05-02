#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 创建一个文件，保存快递柜
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./expressCabinet.db");
    if (!db.open())
    {
        qDebug() << "Unable to open database:" << db.lastError().text();
    }
    // 执行SQl语句
    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS expressCabinet (id INTEGER, status INTEGER,password INTEGER,phoneNumber INTEGER)";
    if (!query.exec(createTableQuery))
    {
        qDebug() << "Failed to create a table:" << query.lastError().text();
    }
    // 初始化柜子
    QSqlTableModel tableModel;
    tableModel.setTable("expressCabinet");
    //初始化10个柜子
    if(!(tableModel.rowCount() == 10))
    {   
        QString deleteQuery = QString("DELETE FROM %1").arg("expressCabinet");
           if (!query.exec(deleteQuery)) {
               qDebug() << "The table could not be emptied " << "expressCabinet" << " data: " << query.lastError().text();
           }
        for (int i = 0; i < 10; i++)
        {
            QString insertQuery = QString("INSERT INTO expressCabinet (id ,status,password,phoneNumber) VALUES (%1,%2,%3,%4)").arg(i).arg(0).arg(0).arg(0);
            if (!query.exec(insertQuery))
            {
                qDebug() << "Failed to insert data:" << query.lastError().text();
            }
        }
    }


    MainWindow w;
    w.show();
    return a.exec();
}
