#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include <iostream>
#include <math.h>
#include <vector>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <Eigen/Dense>
#include "machinevision.h"



class RobotController {
public:
    RobotController(const std::string ipAddress, std::vector<double> &startingPos);
    void connectToRobot(const std::string ip);
    void startingPos();
    std::array<double, 3> getTCP();
    void setR(); //Hard codet pt. men bør hente værider fra database
    void setT(); //-||-
    void moveToPong(/*machineVision &mv*/);
    void calcHInverse();

private:
    double rad = acos(-1)/180;
    std::string ip = "";
    double speed = 1;
    double accel = 1;
    bool async = false;

    // 6 dimentional vector with starting position and orientation of TCP
    std::vector<double> startPos{};

    std::vector<double> pongPos{};

    Eigen::Vector3d T;
    Eigen::Matrix3d R;
    Eigen::Matrix4d H_Inv;

    // Control Interface Object
    ur_rtde::RTDEControlInterface rc;

};

#endif // ROBOTCONTROLLER_H
