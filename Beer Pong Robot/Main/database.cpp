#include "database.h"

Database::Database()
    :db()
{
    std::fixed;
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

void Database::createCell(QString cellName){
    std::cout << "DBIF: Adding " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("INSERT INTO main_db (cell_id) "
                  "VALUES (:cellName)");
    query.bindValue(":cellName", cellName);
    query.exec();
    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::addiptoCell(QString cellName, QString ip){
    std::cout << "DBIF: Adding Robot IP " << ip.toStdString() << " to " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE main_db SET (ur_ip_address) =:ip WHERE (cell_id) = :cellid");
    query.bindValue(":ip", ip);
    query.bindValue(":cellid", cellName);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::addWSGiptoCell(QString cellName, QString ip){
    std::cout << "DBIF: Adding Gripper ip " << ip.toStdString() << " to " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE main_db SET (wsg_ip_address) =:ip WHERE (cell_id) =:cellid");
    query.bindValue(":ip", ip);
    query.bindValue(":cellid", cellName);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::addintrinsicstoCell(QString cellName, QString intrinsics){
    std::cout << "DBIF: Adding intrinsics " << intrinsics.toStdString() << " to " << cellName.toStdString() << std::endl;
    QSqlQuery query;
    query.prepare("UPDATE main_db SET (intrinsics) =:intrinsics WHERE (cell_id) =:cellid");
    query.bindValue(":cellid", cellName);
    query.bindValue(":intrinsics", intrinsics);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::adddistortionparameterstoCell(QString cellName, QString distortionParams){
    std::cout << "Adding distortion parameters " << distortionParams.toStdString() << " to " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE main_db SET (distortion_parameters) =:distortionParam WHERE (cell_id) =:cellid");
    query.bindValue(":cellid", cellName);
    query.bindValue(":distortionParam", distortionParams);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::addTranslationToDB(QString cellName, QString translation){
    std::cout << "Adding translation parameters " << translation.toStdString() << " to " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE main_db SET (translation) =:translation WHERE (cell_id) =:cellid");
    query.bindValue(":cellid", cellName);
    query.bindValue(":translation", translation);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

void Database::addRotationToDB(QString cellName, QString rotation){
    std::cout << "Adding rotation parameters " << rotation.toStdString() << " to " << cellName.toStdString() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE main_db SET (rotation) =:rotation WHERE (cell_id) =:cellid");
    query.bindValue(":cellid", cellName);
    query.bindValue(":rotation", rotation);
    query.exec();

    if(!query.exec()){
        qDebug() << query.lastError();
    }
}

std::vector<double> Database::extractImagePoints(QString cellName) {
    std::cout << "DBIF: Extracting image points for cell #" << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.prepare("SELECT image_points FROM main_db WHERE cell_id = :cellName");
    query.bindValue(":cellName", cellName);
    query.exec();
    while(query.next()){
        //int id = query.value(0).toInt();
        QString val = query.value(0).toString();
        value = val.toUtf8().constData();
        std::cout << "Value: " << value << " | " << std::endl;
    }
    return stringToDoubleVec(value);
}

std::vector<double> Database::extractTranslation(QString cellName){
    std::cout << "DBIF: Extracting translation parameters for cell #" << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.prepare("SELECT translation FROM main_db where cell_id =:cellName");
    query.bindValue(":cellName", cellName);
    query.exec();
    while(query.next()){
        QString val = query.value(0).toString();
        value = val.toUtf8().constData();
        std::cout << "Value: " << value << " | " << std::endl;
    }
    return stringToDoubleVec(value);
}

std::vector<double> Database::extractRotation(QString cellName){
    std::cout << "DBIF: Extracting ratation parameters for cell #" << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.prepare("SELECT rotation FROM main_db where cell_id =:cellName");
    query.bindValue(":cellName", cellName);
    query.exec();
    while(query.next()){
        QString val = query.value(0).toString();
        value = val.toUtf8().constData();
        std::cout << "Value: " << value << " | " << std::endl;
    }
    return stringToDoubleVec(value);
}

std::vector<std::string> Database::extractIPAdresses(int cellId){
    std::cout << "DBIF: Extracting IP Adresses for cell " << cellId << std::endl;
    std::string ur_ip = "";
    std::string wsg_ip = "";
    QSqlQuery query;
    query.prepare("SELECT ur_ip_address, wsg_ip_address FROM main_db WHERE id =:cellId");
    query.bindValue(":cellId", cellId);
    query.exec();
    if(!query.exec()) {
        qDebug() << query.lastError();
    }
    while(query.next()){
        QString val1 = query.value(0).toString();
        //std::cout << val1.toUtf8().constData() << " ";
        ur_ip = val1.toUtf8().constData();
        QString val2 = query.value(1).toString();
        // std::cout << val1.toUtf8().constData() << std::endl;
        wsg_ip = val2.toUtf8().constData();
    }

    // std::cout << "ur ip: " << ur_ip << " | " << "wsg ip: " << wsg_ip << " | " << std::endl;
    std::vector<std::string> temp;
    temp.emplace_back(ur_ip);
    temp.emplace_back(wsg_ip);

    return temp;
}

std::vector<double> Database::extractIntrinsics(int cellId){
    std::cout << "DBIF: Extracting intrinsics for cell " << cellId << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.prepare("SELECT intrinsics FROM main_db WHERE id =:cellId");
    query.bindValue(":cellId", cellId);
    query.exec();
    if(!query.exec()) {
        qDebug() << query.lastError();
    }
    while(query.next()){
        QString val1 = query.value(0).toString();
        //std::cout << val1.toUtf8().constData() << " ";
        value = val1.toUtf8().constData();

    }
    return stringToDoubleVec(value);
}

std::vector<double> Database::extractDistortionParameters(int cellId){
    std::cout << "DBIF: Extracting distortion parameters for cell " << cellId << std::endl;
    std::string value = "";
    QSqlQuery query;
    query.prepare("SELECT distortion_parameters FROM main_db WHERE id =:cellId");
    query.bindValue(":cellId", cellId);
    query.exec();
    if(!query.exec()) {
        qDebug() << query.lastError();
    }
    while(query.next()){
        QString val1 = query.value(0).toString();
        //std::cout << val1.toUtf8().constData() << " ";
        value = val1.toUtf8().constData();

    }
    return stringToDoubleVec(value);
}

void Database::insertData(std::string data){
    std::cout << "DBIF: Inserting data to database" << std::endl;
    QSqlQuery query;
    query.prepare("INSERT INTO main_db (name) "
                  "VALUES (:name)");

    query.bindValue(":name", "1, 2, 3, 4");
    query.exec();
}

void Database::disconnect(){
    std::cout << "DBIF: Disconnecting from database" << std::endl;
    db.close();
}

std::vector<double> Database::stringToDoubleVec(const std::string inStr){

    //std::cout << "DBIF: Input string: " << inStr << std::endl;
    //std::cout << "DBIF: Converting to float array" << std::endl;

    std::vector<double> vec = {};

    std::string s = inStr;
    std::string delimiter = ", ";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        vec.push_back(stod(token));
        s.erase(0, pos + delimiter.length());
    }
    vec.push_back(stod(s));

    /*std::cout << "\nDBIF: Output of conversion:\n[";

    for (int i = 0; i < vec.size(); i++) {
        if(i < vec.size()) {
            std::cout << vec.at(i) << ", ";
        } else {
            std::cout << vec.at(i) << "]" << std::endl;
        }
    }
    std::cout << std::endl;*/

    return vec;
}

void Database::kastOutcome(QString cellname, int kast){
    // 0 = ikke ramt | 1 = ramt
    std::cout << "DBIF: Adding throw outcome" << std::endl;

    QSqlQuery query;
    query.prepare("INSERT INTO kast (cell_id, ramt)"
                  "VALUES (:cellName, :ramt)");
    query.bindValue(":cellName", cellname);
    query.bindValue(":ramt", kast);
    query.exec();
}

void Database::printAccuracy(QString cellId){
    int i;
    QSqlQuery query;
    query.prepare("select (cast((select count(ramt) from kast where ramt > 0 and cell_id =:cellid) as real)) / (cast((select count(ramt) from kast where cell_id =:cellid) as real)) * 100;");
    query.bindValue(":cellid", cellId);
    query.exec();
    while(query.next()){
        i = query.value(0).toInt();
    }
    std::string acc = "DBIF: Average accuracy of " << cellId.toUtf8().constData() << " " << std::to_string(i) << "%";
}

std::string Database::arrayToString(double array[6]){
    std::string value = "";
    //std::cout << sizeof(array) << std::endl;
    //int len = sizeof(array)/sizeof(*array);
    for (int i = 0; i < 6; i++) {
        if(i == 0){
        std::cout << array[i] << std::endl;
        value.append(std::to_string(array[i]));

}
        else{
            std::cout << array[i] << std::endl;
            value += ", ";
            value.append(std::to_string(array[i]));

        }
    }
    return value;
}

std::string Database::vecToString(std::vector<double> vect){
    std::string value = "";
    for (int i = 0; i < 3; ++i) {
        if(i == 0){
            std::cout << vect[i] << std::endl;
            value.append(std::to_string(vect[i]));
        }
        else {

            std::cout << vect[i] << std::endl;
            value.append(", ");
            value.append(std::to_string(vect[i]));

        }

    }
    return value;

}

std::vector<double> Database::stringToVec(std::string val){
    std::vector<double> vec = {};

    std::string s = val;
    std::string delimiter = ", ";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        vec.push_back(stod(token));
        s.erase(0, pos + delimiter.length());
    }
    vec.push_back(stod(s));

    return vec;

}
