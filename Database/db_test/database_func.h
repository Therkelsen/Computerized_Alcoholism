#ifndef DATABASE_FUNC_H
#define DATABASE_FUNC_H
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlDriver>
#include <QString>

class Database_func
{
public:
    Database_func();
    void SendDatadb();
    void ReceiveDatadb();
    void CloseConndb();

private:
    QSqlDatabase db;


};

#endif // DATABASE_FUNC_H
