#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include <iostream>
#include <math.h>
#include <vector>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <Eigen/Dense>
#include "machinevision.h"
#include <rl/hal/WeissWsg50.h>




class RobotController {
public:
    RobotController(const std::string ipAddress, const std::string gripIP);
    void connectToRobot(const std::string ip);
    void startingPos();
    std::array<double, 3> getTCP();
    void setR(); //Hard codet pt. men bør hente værider fra database
    void setT(); //-||-
    void calcHInverse();
    void moveToPong(machineVision &mv);
    void moveDown(double down);
    void moveUp(double up);
    void grip();
    void releaseGrip();
    void throwPose(); //Mangler implementation
    void stopGripper();



private:
    double rad = acos(-1)/180;
    std::string ip = "";
    double speed = 1;
    double accel = 1;
    bool async = false;

    std::string gripperIP = "";

    // 6 dimentional vector with starting position and orientation of TCP
    std::vector<double> startPos{0.143, -0.220, 0.241, 2.599, -1.792, 0};
    std::vector<double> throwPos{0.132, -0.255, 0.251, 2.599, -1.792, 0};

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

};

#endif // ROBOTCONTROLLER_H
