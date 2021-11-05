#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include <iostream>
#include <vector>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_io_interface.h>
#include <ur_rtde/rtde.h>
#include <ur_rtde/script_client.h>
#include <ur_rtde/dashboard_client.h>
#include <ur_rtde/robotiq_gripper.h>


class RobotController
{
public:
    RobotController(const std::string ipAddress, std::vector<double> &startingPos);
    void connectToRobot(const std::string ip);
    void startingPos();
    void setPongPos(std::vector<double> &pongCoordinates);
    void setRobToPong();
    void moveToPong();
    void gripAndLift();
    void printPose(std::vector<double> &inPose, double inSpeed, double inAccel, bool inAsync, const std::string inName, const std::string inType);

private:
    double rad = M_PI/180;

    double speed = 1;
    double accel = 1;
    bool async = false;

    // 6 dimentional vector with starting position and orientation of TCP
    std::vector<double> startPos{};

    // position of pong in camera coordinates
    std::vector<double> pongPos;

    // position of pong in robot coordinates
    std::vector<double> robToPong;

    std::vector<double> abovePong;
    std::vector<double> atPong;

    // Control Interface Object
    ur_rtde::RTDEControlInterface rc;

};

#endif // ROBOTCONTROLLER_H
