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
    float* extractIPAdresses(int cellId);
    float* extractIntrinsics(int cellId);
    float* extractDistortionParameters(int cellId);
    void disconnect();
    float* stringToFloatArray(const std::string inStr);

private:
    QSqlDatabase db;


};

#endif // DATABASE´_H
