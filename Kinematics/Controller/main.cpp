
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
#include <ur_rtde/rtde_control_interface.h>

using namespace std;

int main() {
    // Create strings to contain ip adresses
    const string ipPhysical = "192.168.100.49";
    const string ipSimulator = "127.0.0.1";
    string ip = ipSimulator;

    // ([mm], [mm], [mm], [rad], [rad], [rad])
    std::vector<double> startPos{160,-475,415,0,0,0};

    try {
        cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;

        // Create RobotController object
        RobotController rc(ip, startPos);

        machineVision mv();

        std::vector<double> vector = mv.getObject(1);

       /* for (unsigned int i  = 0; i < vector.size(); ++i) {
            std::cout << vector.at(i);
        }*/

        cout << "UR_RTDE: Connected to robot socket at " << ip << "\n" << endl;

        rc.startingPos();

        Calib cal1(rc);

        cal1.printCoordinates(std::cout);



    } catch (const runtime_error& error) {
        cout << "UR_RTDE: Failed connecting to robot socket at " << ip << "\n" << endl;
        cout << "System : Exiting" << endl;
        return -1;
    }

    return 0;
}
