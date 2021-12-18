#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <Eigen/Dense>
#include "machinevision.h"
#include "database.h"
#include <rl/hal/WeissWsg50.h>

class RobotController {
public:
    int cellId;
    std::string cellIdString;
    RobotController(const std::string ipAddress, const std::string gripIP);
    void connectToRobot(const std::string ip);
    void startingPos();
    std::array<double, 3> getTCP();
    void setR(); //Hard codet pt. men bør hente værider fra database
    void setT(); //-||-
    void calcHInverse();
    void moveToPong(machineVision &mv);
    Eigen::Vector4d getRobCoords(machineVision &mv);
    void moveDown(double down);
    void moveUp(double up);
    void grip();
    void releaseGrip(double T);
    void startThrowPose(std::vector<double> startThrowPos);
    std::vector<double> getEndThrowPose();
    void stopGripper();
    void throwPong(std::vector<double> QDot, std::vector<double> Accel, double T);
    void stopThrow();



private:
    double rad = acos(-1)/180;
    std::string ip = "";
    double speed = 1;
    double accel = 1;
    bool async = false;

    std::string gripperIP = "";

    // 6 dimentional vector with starting position and orientation of TCP
    std::vector<double> startPos{0.143, -0.220, 0.241, 2.599, -1.792, 0};
    std::vector<double> endThrowPos{0.122, -0.357, 0.600, 1.527, -1.043, 1.457};

    std::vector<double> pongPos{};

    Eigen::Vector3d T;
    Eigen::Matrix3d R;
    Eigen::Matrix4d H_Inv;

    // Control Interface Object
    ur_rtde::RTDEControlInterface rc;
    //Receive interface
    ur_rtde::RTDEReceiveInterface rr;

    //gripper controll object
    rl::hal::WeissWsg50 gc;

    //database object
    Database db;

};

#endif // ROBOTCONTROLLER_H
