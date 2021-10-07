#include <iostream>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_io_interface.h>
#include <ur_rtde/rtde.h>
#include <ur_rtde/script_client.h>
#include <ur_rtde/dashboard_client.h>
#include <ur_rtde/robotiq_gripper.h>

using namespace std;

int main() {
  // Create strings to contain ip adresses
  const std::string ipPhysical = "192.168.100.49";
  const std::string ipSimulator = "127.0.0.1";
  std::string ip = ipSimulator;

  try {
    // Connect to the robot socket

    cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;
    ur_rtde::RTDEControlInterface rtde_control(ip);

    cout << "UR_RTDE: Connected to robot socket at " << ip << " " << endl;

    double rad = M_PI/180;

    // Send robot to base position
    // (const std::vector<double> &q, double speed = 1.05, double acceleration = 1.4, bool async = false)
    std::vector<double> jPose{-90*rad,-90*rad,-135*rad,0*rad,90*rad,0*rad};

    double speed = 1;
    double accel = 1;
    bool async = false;

    cout << "UR_RTDE: Sending joint pose (" << jPose.at(0) << "," << jPose.at(1) << ","  << jPose.at(2) << ","  << jPose.at(3) << ","  << jPose.at(4) << ","  << jPose.at(5) << ") to Robot using moveJ" << endl;
    rtde_control.moveJ(jPose, speed, accel, async);

  } catch (const runtime_error& error) {
    cout << "UR_RTDE: Failed connecting to robot socket at " << ip << " " << endl;
    cout << "System : Exiting" << endl;
    return -1;
  }

  return 0;
}
