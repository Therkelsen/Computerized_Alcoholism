
/*
*  Implementation of ur_rtde library @ https://sdurobotics.gitlab.io/ur_rtde/index.html
*  Created October 4th, 2021
*  Authored by Thomas Therkelsen @
*/

#include <iostream>
#include <iomanip>
#include "robotcontroller.h"

using namespace std;

int main() {
    // Create strings to contain ip adresses
    const string ipPhysical = "192.168.100.49";
    const string ipSimulator = "127.0.0.1";
    string ip = ipSimulator;

    std::vector<double> startPos{182.90, -288.56, 427.56, 1.576, 2.378, -0.256};

    try {
        cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;

        RobotController rc(ip, startPos);
        cout << "UR_RTDE: Connected to robot socket at " << ip << "\n" << endl;

        // Connect to the robot socket
        cout << boolalpha;

    } catch (const runtime_error& error) {
        cout << "UR_RTDE: Failed connecting to robot socket at " << ip << "\n" << endl;
        cout << "System : Exiting" << endl;
        return -1;
    }

    return 0;
}
