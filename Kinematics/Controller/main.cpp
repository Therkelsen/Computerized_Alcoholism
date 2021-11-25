
/*
*  Main program for pong robot
*  Created October 4th, 2021
*  Authored by Thomas Therkelsen @ SDU
*/


#include "robotcontroller.h"
#include "calib.h"
#include "machinevision.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <array>
#include <ur_rtde/rtde_control_interface.h>

using namespace std;

int main() {
    // Create strings to contain ip adresses
    const string ipPhysical = "192.168.100.49";
    const string ipSimulator = "127.0.0.1";
    string ip = ipPhysical;

    // ([mm], [mm], [mm], [rad], [rad], [rad])
    std::vector<double> startPos{160,-475,415,0,0,0};

    try {
         cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;

        // Create RobotController object
           RobotController rc(ip, startPos);

          cout << "UR_RTDE: Connected to robot socket at " << ip << "\n" << endl;



          //machineVision mv;

        /*  rc.setR();
          rc.setT();
          rc.calcHInverse();


          rc.moveToPong();
*/
        //////Calibration///////

        //machineVision mv;

        //Calib cal1(rc, mv, std::cout, std::cin);

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




    } catch (const runtime_error& error) {
        cout << "UR_RTDE: Failed connecting to robot socket at " << ip << "\n" << endl;
        cout << "System : Exiting" << endl;
        return -1;
    }

    return 0;
}
