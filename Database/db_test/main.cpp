

#include "database.h"

using namespace std;

void setup(Database db) {
    int state = 0;
    int cellId;
    std::string choice;
    std::string cellIdString = "cell ";
    std::string robotIPAddress, gripperIPAddress;
    cout << "System: Initializing program" << endl;
    while(state != -1) {
            switch (state) {
                case 0:
                    cout << "System: Which robot cell are you currently seated at?" << endl;
                    cin >> cellId;
                    state = 1;
                    break;

                case 1:
                    cout << "System: You have chosen robot cell " << cellId << "\n" <<
                            "System: Is this the right one? (y or n)" << endl;
                    cin >> choice;
                    if(choice == "y") {
                        cout << "System: You have confirmed the choice of robot cell " << cellId << "\n" << endl;
                        cellIdString.append(to_string(cellId));
                        state = 2;
                    } else {
                        state = 0;
                    }
                    break;

                case 2:
                    //double ips[2] = db.extractIPAdresses(cellId);
                    db.extractIPAdresses(cellId);
                    //cout << "ips: " << ips[1] << " & " << ips[2] << endl;
                    state = -1;
                    break;
                default:
                    break;
            }
    }
}

int main() {
    Database db;
    db.extractIPAdresses(1);
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
    setup(db);

}



