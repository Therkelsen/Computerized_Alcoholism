
/*
*  Main program for pong robot
*  Created October 4th, 2021
*  Authored by Thomas Therkelsen @ SDU
*/

#include "database.h"
#include "robotcontroller.h"
#include "calib.h"
#include "machinevision.h"
#include "projectilemotion.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <array>
#include <ur_rtde/rtde_control_interface.h>
#include <rl/hal/WeissWsg50.h>
#include <chrono>
#include <thread>

using namespace std;

// Create strings to contain ip adresses
string ipPhysical = "192.168.100.30";
string ipSimulator = "127.0.0.1";
string ipGripper = "192.168.100.10";
string ipRobot;
int cellId;
std::string cellIdString = "cell ";

void setup(Database db) {
    int state = 0;
    std::string choice;
    QString intrinsics = "443.30481, 0, 719.5, 0, 471.87396, 539.5, 0, 0, 1";
    QString distortion = "-0.0306633, 0.000208614, 0.000163452, -0.00413883, -3.86967e-07";
    std::string robotIPAddress, gripperIPAddress;
    std::vector<std::string> ips;
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
                        cellIdString.append(std::to_string(cellId));
                        cout << "cellIdString: " << cellIdString << endl;
                        state = 2;
                    } else {
                        state = 0;
                    }
                    break;

                case 2:
                    //double ips[2] = db.extractIPAdresses(cellId);
                    ips = db.extractIPAdresses(cellId);
                    ipRobot = ips.at(0);
                    ipGripper = ips.at(1);
                    state = -1;
                    break;
                default:
                    break;
            }
    }
}

int main() {
    Database db;
    setup(db);

    std::fixed;

    try {
        cout << "UR_RTDE: Attempting connection to robot socket at " << ipRobot << " " << endl;

        // Create RobotController object
        RobotController rc(ipRobot, ipGripper);
        rc.cellId = cellId;
        rc.cellIdString = cellIdString;
        cout << "rc cellIdString " << cellIdString << endl;

        cout << "UR_RTDE: Connected to robot socket at " << ipRobot << "\n" << endl;
        std::cout << "tis" << std::endl;

        machineVision mv(cellId, QString::fromStdString(cellIdString));
        cout << "mv cellIdString " << cellIdString << endl;

        rc.startingPos();

        rc.setR();
        rc.setT();
        rc.calcHInverse();

        rc.moveToPong(mv);

        rc.moveDown(0.032);

        rc.grip();

        rc.moveUp(0.032);

        Eigen::Vector4d cup = rc.getRobCoords(mv);
        std::cout << "Cup : \n" << cup << "\n" << std::endl;

        projectileMotion pm;
        std::vector<double> startThrowPos = pm.getStartThrowPos(cup, 0.4, rc);

        rc.startThrowPose(startThrowPos);

        //std::vector<double> endPos = {1.8260, -1.7520, 1.7001, -3.0770, -1.4902, 0.0};
        //rc.startThrowPose(endPos);

        std::vector<double> qd = pm.getQDot();
        std::vector<double> accel = pm.getAccel();
        double T = pm.getTEnd();
        std::cout << "QDot:" << std::endl;
        for(int i = 0; i < 6; i++){
            std::cout << qd.at(i) << std::endl;
        }
        std::cout << "Accel:" << std::endl;
        for(int i = 0; i < 6; i++){
            std::cout << accel.at(i) << std::endl;
        }
        std::cout << "T:" << std::endl;
        std::cout << T << std::endl;
        double tEnd = pm.getTEnd();
        std::thread t1(&RobotController::releaseGrip, &rc, tEnd);
        rc.throwPong(qd, accel, T);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tEnd*1000)));
        rc.stopThrow();
        t1.join();

        rc.stopGripper();
        // machineVision mv;

        //////Calibration///////

        //machineVision mv;

        //Calib cal1(rc, mv, std::cout, std::cin);
        /*
        Calib calTest;

        calTest.printCoordinates(std::cout);

        calTest.convertToEigen();
        calTest.calcCentroids();
        calTest.calcQ();
        calTest.calcH();
        calTest.calcSVD();
        calTest.calcRot();
        calTest.calcTrans();
        calTest.printCalibration();


        rc.setR();
        rc.setT();
        rc.calcHInverse();

        rc.moveToPong(mv);

        rc.moveDown(0.032);

        rc.grip();

        rc.moveUp(0.032);

        //rc.throwPose();

        rc.releaseGrip();

        rc.stopGripper();
*/



    std::cout << "fissekal" << std::endl;

    } catch (const runtime_error& error) {
        cout << "UR_RTDE: Failed connecting to robot socket at " << ipRobot << "\n" << endl;
        cout << "System : Exiting" << endl;
        return -1;
    }



    return 0;

}



