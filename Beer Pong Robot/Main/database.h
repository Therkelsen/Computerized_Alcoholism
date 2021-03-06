#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlDriver>
#include <QString>
#include <QDebug>

class Database
{
public:
    Database();
    void insertData(std::string data);
    void extractData();
    void createCell(QString cellName);
    void addIPToCell(QString cellName, QString ip);
    void addWSGIPToCell(QString cellName, QString ip);
    void addIntrinsicsToCell(QString cellName, QString intrinsics);
    void addDistortionParametersToCell(QString cellName, QString distortionParams);
    void addTranslationToDB(QString cellName, QString translation);
    void addRotationToDB(QString cellName, QString rotation);
    std::vector<double> extractImagePoints(QString cellName);
    std::vector<double> extractTranslation(QString cellName);
    std::vector<double> extractRotation(QString cellName);
    std::vector<std::string> extractIPAdresses(int cellId);
    std::vector<double> extractIntrinsics(int cellId);
    std::vector<double> extractDistortionParameters(int cellId);
    void disconnect();
    std::vector<double> stringToDoubleVec(const std::string inStr);
    void kastOutcome(QString cellname, int kast);
    std::string accuracy(QString cellId);
    std::string arrayToString(double array[6]); //måske brug eigen
    std::string vecToString(std::vector<double> vect);
    std::vector<double> stringToVec(std::string val);

private:
    QSqlDatabase db;


};

#endif // DATABASE´_H
