#include "database_func.h"

Database_func::Database_func()
    :db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/host/Documents/project_db.db");


    //std::cout << db.open() << std::endl;
    if (!db.open()){
        std::cout << "Failed to load database" << std::endl;
    }
    else{
        std::cout << "Database loaded" << std::endl;
        std::cout << "*********************************************" << std::endl << std::endl;
    }

}
void Database_func::ReceiveDatadb(){
    // ##################### Select data from database #####################
    QSqlQuery query;
    query.exec("SELECT * FROM main_db");
    while(query.next()){
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        std::string name2 = name.toUtf8().constData();
        std::cout << "ID: " << id << " | " << "Name: " << name2 << " | " << std::endl;
    }
}

void Database_func::SendDatadb(){
    // ##################### Insert data into database #####################


    std::cout << "*********************************************" << std::endl << std::endl;
    std::cout << "Inserting data to database" << std::endl;
    QSqlQuery query;
    query.prepare("INSERT INTO main_db (name) "
                  "VALUES (:name)");

    query.bindValue(":name", "1,2,3,4,5");
    query.exec();
    std::cout << "*********************************************" << std::endl << std::endl;
}

void Database_func::CloseConndb()
{
    db.close();
}
