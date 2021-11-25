#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlDriver>
#include <QString>

class Database
{
public:
    Database();
    void insertData(std::string data);
    void extractData();
    double* extractIPAdresses(int cellId);
    double* extractIntrinsics(int cellId);
    double* extractDistortionParameters(int cellId);
    void disconnect();
    double* stringToDoubleArray(const std::string inStr);

private:
    QSqlDatabase db;


};

#endif // DATABASE´_H
