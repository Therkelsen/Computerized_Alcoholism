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
    void createCell(QString cellName);
    void addiptoCell(QString cellName, QString ip);
    void addWSGiptoCell(QString cellName, QString ip);
    void addintrinsicstoCell(QString cellName, QString intrinsics);
    void adddistortionparameterstoCell(QString cellName, QString distortionParams);
    void addTranslationToDB(QString cellName, QString translation);
    void addRotationToDB(QString cellName, QString rotation);
    std::string extractTranslation(QString cellName);
    std::string extractRotation(QString cellName);
    double* extractIPAdresses(int cellId);
    double* extractIntrinsics(int cellId);
    double* extractDistortionParameters(int cellId);
    void disconnect();
    double* stringToDoubleArray(const std::string inStr);
    void kastOutcome(QString cellname, int kast);
    std::string accuracy(QString cellId);
    std::string arrayToString(double array[]); //måske brug eigen
    std::string vecToString(std::vector<double> vect);
    std::vector<std::string> stringToVec();

private:
    QSqlDatabase db;


};

#endif // DATABASE´_H
