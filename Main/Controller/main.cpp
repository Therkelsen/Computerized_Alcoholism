
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
#include <rl/hal/WeissWsg50.h>
#include <chrono>
#include <thread>


using namespace std;

int main() {
    // Create strings to contain ip adresses
    const string ipPhysical = "192.168.100.30";
    const string ipSimulator = "127.0.0.1";
    string ip = ipPhysical;

    const string ipGripper = "192.168.100.10";


    try {
        cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;

        // Create RobotController object
        RobotController rc(ip, ipGripper);


        cout << "UR_RTDE: Connected to robot socket at " << ip << "\n" << endl;



         machineVision mv;


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

*/
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



    } catch (const runtime_error& error) {
        cout << "UR_RTDE: Failed connecting to robot socket at " << ip << "\n" << endl;
        cout << "System : Exiting" << endl;
        return -1;
    }



    return 0;
}
