

#include "database.h"

int main()
{
    Database db;

    //std::string intrinsics = "443.30481, 0, 719.5, 0, 471.87396, 539.5, 0, 0, 1";

    //    db.stringToDoubleArray(intrinsics);
    //db.extractIPAdresses(1);
    //db.extractIPAdresses(2);
    //db.extractIPAdresses(3);
    //db.extractIPAdresses(4);
    /*db.addiptoCell("cell 5", "192.168.1.6");
    db.addintrinsicstoCell("cell 5", "443.30481, 0, 719.5, 0, 471.87396, 539.5, 1, 1, 1");
    db.addWSGiptoCell("cell 5", "182.168.10.10");
    db.adddistortionparameterstoCell("cell 5", "1.2.3.4.5");
    db.kastOutcome("cell 5", 0);
    std::cout << db.accuracy("cell 5") << std::endl;*/
    //db.addRotationToDB("cell 5", "12345");
    //db.extractRotation("cell 5");
   /* double x[] = {
            4.2201,
            2.0035,
            6.1921,
            1.2396,
            1.3023,
            2.0334
          };
    db.addRotationToDB("cell 5", QString::fromStdString(db.arrayToString(x)));*/
    //std::vector<double> vec = {1.1,2.2,3.3};
    //std::cout << db.vecToString(vec) << std::endl;
    std::string val = "1.1, 2.2, 3.3";
    std::cout << db.stringToVec(val) << std::endl;

}



