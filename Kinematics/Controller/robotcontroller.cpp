
/*
*  Class implementation of ur_rtde library @ https://sdurobotics.gitlab.io/ur_rtde/index.html
*  Created November 3rd, 2021
*  Authored by Thomas Therkelsen @ SDU
*/

#include "robotcontroller.h"

RobotController::RobotController(const std::string ipAddress, std::vector<double> &startingPos)
  :rc(ipAddress), startPos(startingPos) {
  robToPong.reserve(2);
  abovePong.reserve(6);
  atPong.reserve(6);
}

void RobotController::startingPos() {
    // Send robot to base position
    printPose(startPos, speed, accel, async, "startPos", "moveJ");
    rc.moveJ(startPos, speed, accel, async);

}

void RobotController::setPongPos(std::vector<double> &pongCoordinates) {
    pongPos = pongCoordinates;
}

void RobotController::setRobToPong() {
    robToPong.insert(robToPong.begin() + 0, pongPos.at(0) - 850);
    robToPong.insert(robToPong.begin() + 1, pongPos.at(1) - 300);
}

void RobotController::moveToPong() {
    printPose(abovePong, speed, accel, async, "abovePong", "moveL");
    rc.moveL(abovePong, speed, accel, async);
}

void RobotController::gripAndLift() {
    // IO code for opening gripper

    //_________________________________________________/

    // Move TCP to ball
    printPose(atPong, speed, accel, async, "atPong", "moveL");
    rc.moveL(atPong, speed, accel, async);

    // IO code for closing gripper

    //_____________________________________________/

    // Lift ball
    printPose(abovePong, speed, accel, async, "abovePong", "moveL");
    rc.moveL(abovePong, speed, accel, async);
}

void RobotController::printPose(std::vector<double> &inPose, double inSpeed, double inAccel, bool inAsync, const std::string inName, const std::string inType) {
  std::vector<double> pose = inPose;
  double speed = inSpeed;
  double accel = inAccel;
  bool async = inAsync;
  std::string name = inName;
  std::string type = inType;

  std::cout << "UR_RTDE: Sending joint pose to Robot using " << type << std::endl;
  std::cout << "         " << name << " [rad]: (";

  for (int i = 0; i < pose.size(); i++) {
      if (i < pose.size()-1) {
          std::cout << pose.at(i) << ", ";
      } else {
          std::cout << pose.at(i) << ")" << std::endl;
      }
  }

  std::cout << "         Speed [unit]: " << speed;
  std::cout << "\n         Acceleration [unit]: " << accel;
  std::cout << "\n         Async: " << async << "\n" << std::endl;
}






