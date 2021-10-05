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
  const std::string ipPhysical = "192.168.100.49";
  const std::string ipSimulator = "127.0.0.1";
  std::string ip = ipSimulator;


  cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;
  ur_rtde::RTDEControlInterface rtde_control(ip);

  /*
  try {
    cout << "UR_RTDE: Attempting connection to robot socket at " << ip << " " << endl;
    ur_rtde::RTDEControlInterface rtde_control(ip);

  }
  catch (const runtime_error& error) {
    cout << "UR_RTDE: Failed connecting to robot socket at " << ip << " " << endl;
    return -1;
  }
  */

  cout << "UR_RTDE: Connected to robot socket at " << ip << " " << endl;

  // (const std::vector<double> &q, double speed = 1.05, double acceleration = 1.4, bool async = false)
  std::vector<double> jPose{-90,-90,-135,0,90,0};
  double speed = 1;
  double accel = 1;
  bool async = false;
  rtde_control.moveJ(jPose, speed, accel, async);

  return 0;
}
