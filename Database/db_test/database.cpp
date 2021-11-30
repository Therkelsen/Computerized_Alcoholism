#include "database.h"

Database::Database()
    :db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../project_db.db");


    //std::cout << db.open() << std::endl;
    if (!db.open()){
        std::cout << "DBIF: Failed to load database" << std::endl;
    }
    else{
        std::cout << "DBIF: Database loaded" << std::endl;
    }

}

void Database::extractData(){
    QSqlQuery query;
    std::string value = "";
    query.exec("SELECT * FROM main_db");
    while(query.next()){
        int id = query.value(0).toInt();
        QString val = query.value(1).toString();
        value = val.toUtf8().constData();
        std::cout << "ID: " << id << " | " << "Value: " << value << " | " << std::endl;
    }
}

void Database::createCell(std::string cellName)
{

}

void Database::addiptoCell(std::string cellName, std::string ip)
{

}

void Database::addintrinsicstoCell(std::string cellName, std::string intrinsics)
{

}

void Database::adddistortionparameterstoCell(std::string cellName, std::string distortionParams)
{

}

double* Database::extractIPAdresses(int cellId){
    std::fixed;
    std::cout << "DBIF: Extracting IP Adresses for cell #" << cellId << std::endl;
    std::string ur_ip = "";
    std::string wsg_ip = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM main_db where id =:cId");
    query.bindValue(":cId", cellId);
    query.exec();
    while(query.next()){
        QString val1 = query.value(2).toString();
        ur_ip = val1.toUtf8().constData();
        QString val2 = query.value(3).toString();
        wsg_ip = val2.toUtf8().constData();


    }
    std::cout << "ur ip: " << ur_ip << " | " << "wsg ip: " << wsg_ip << " | " << std::endl;
    return stringToDoubleArray(ur_ip);
}

double* Database::extractIntrinsics(int cellId){
    std::cout << "DBIF: Extracting intrinsics for cell #" << cellId << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.exec("SELECT * FROM main_db");
    while(query.next()){
        int id = query.value(0).toInt();
        QString val = query.value(1).toString();
        value = val.toUtf8().constData();
        std::cout << "ID: " << id << " | " << "Value: " << value << " | " << std::endl;
    }
    return stringToDoubleArray(value);
}

double* Database::extractDistortionParameters(int cellId){
    std::cout << "DBIF: Extracting distortion parameters for cell #" << cellId << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.exec("SELECT * FROM main_db");
    while(query.next()){
        int id = query.value(0).toInt();
        QString val = query.value(1).toString();
        value = val.toUtf8().constData();
        std::cout << "ID: " << id << " | " << "Value: " << value << " | " << std::endl;
    }
    return stringToDoubleArray(value);
}

void Database::insertData(std::string data){
    std::cout << "DBIF: Inserting data to database" << std::endl;
    QSqlQuery query;
    query.prepare("INSERT INTO main_db (name) "
                  "VALUES (:name)");

    query.bindValue(":name", "1, 2, 3, 4");
    query.exec();
}

void Database::disconnect() {
    std::cout << "DBIF: Disconnecting from database" << std::endl;
    db.close();
}

double* Database::stringToDoubleArray(const std::string inStr) {

  std::cout << "DBIF: Input string: " << inStr << std::endl;
  std::cout << "DBIF: Converting to float array" << std::endl;

  std::vector<std::string> vec = {};

  std::string s = inStr;
  std::string delimiter = ", ";
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      vec.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  vec.push_back(s);


  double *arr = new double[vec.size()];
  for (int i = 0; i < vec.size(); i++) {
      double x = std::stof(vec.at(i));
      arr[i] = x;
  }

  std::cout << "\nDBIF: Output of conversion:\n[";

  for (int i = 0; i < sizeof(arr) + 1; i++) {
      if(i < sizeof(arr)) {
          std::cout << arr[i] << ", ";
      } else {
          std::cout << arr[i] << "]" << std::endl;
      }
  }
  std::cout << std::endl;

  return arr;
}
