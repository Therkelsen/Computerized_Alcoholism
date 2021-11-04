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
    void StartingPos();
    void setPongPos(std::vector<double> &pongCoordinates);
    void setRobToPong();
    void moveToPong();
    void gripAndLift();

private:
    double speed = 1;
    double accel = 1;
    bool async = false;

    // 6 dimentional vector with starting position and orientation of TCP
    std::vector<double> startPos;

    // position of pong in camera coordinates
    std::vector<double> pongPos;

    // position of pong in robot coordinates
    std::vector<double> robToPong;

    std::vector<double> abovePong{robToPong.at(0), robToPong.at(1), 100, startPos.at(3), startPos.at(4), startPos.at(5)};
    std::vector<double> atPong{robToPong.at(0), robToPong.at(1), 15, startPos.at(3), startPos.at(4), startPos.at(5)};

    // Control Interface Object
    ur_rtde::RTDEControlInterface rc;

};

#endif // ROBOTCONTROLLER_H
