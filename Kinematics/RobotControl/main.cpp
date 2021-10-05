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

    // Send robot to base position
    // (const std::vector<double> &q, double speed = 1.05, double acceleration = 1.4, bool async = false)
    std::vector<double> jPose{-90,-90,-135,0,90,0};
    double speed = 1;
    double accel = 1;
    bool async = false;
    rtde_control.moveJ_IK(jPose, speed, accel, async);

  }
  catch (const runtime_error& error) {
    cout << "UR_RTDE: Failed connecting to robot socket at " << ip << " " << endl;
    cout << "System : Exiting" << endl;
    return -1;
  }

  return 0;
}
