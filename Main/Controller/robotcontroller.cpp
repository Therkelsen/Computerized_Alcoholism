
/*
*  Class implementation of ur_rtde library @ https://sdurobotics.gitlab.io/ur_rtde/index.html
*  Created November 3rd, 2021
*  Authored by Thomas Therkelsen @ SDU
*/

#include "robotcontroller.h"



RobotController::RobotController(const std::string ipAddress)
  :rc(ipAddress), rr(ipAddress) {
  std::cout << std::boolalpha;

  ip = ipAddress;
}

void RobotController::startingPos() {
    // Send robot to base position

    rc.moveL(startPos);
}

std::array<double, 3> RobotController::getTCP() {

    std::vector<double> TCP = rr.getActualTCPPose();

    for (unsigned int i = 0; i < TCP.size(); ++i) {
        std::cout << TCP.at(i) << " ";
    }

    std::array<double, 3> TCPPose;

    //Copies TCP and converts to mm

    for (unsigned int i = 0; i < 3; ++i) {
        TCPPose.at(i) = TCP.at(i) * 1000;
    }

    return TCPPose;

}

void RobotController::setR() {

    R(0,0) = -0.38;
    R(0,1) = 0.93;
    R(0,2) = 0.00;
    R(1,0) = -0.93;
    R(1,1) = -0.38;
    R(1,2) = -0.00;
    R(2,0) = 0.00;
    R(2,1) = -0.00;
    R(2,2) = 1.00;
}

void RobotController::setT() {
    T = {821.89, 276.86, -210};

}

void RobotController::calcHInverse() {


    Eigen::Matrix4d H;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            H(i,j) = R(i,j);
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        H(i,3) = T(i);
    }

    for (unsigned int i = 0; i < 4; ++i) {
        if (i == 3) {
           H(3,i) = 1;
        } else {
           H(3,i) = 0;
        }
    }

    std::cout << "\n\nH: ";
    for (unsigned int i = 0; i < 4; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 4; ++j) {
            std::cout << H(i,j) << " ";
        }
    }
    std::cout << "\n";

    H_Inv = H.inverse();

    //testudskrivning af H_Inv
    std::cout << "H_Inv : \n";
    for (unsigned int i = 0; i < 4; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 4; ++j) {
            std::cout << H_Inv(i,j) << " ";
        }
    }

    std::cout << "\n";


}

void RobotController::moveToPong(machineVision &mv)  {
    pongPos = mv.getObject(1);

    Eigen::Vector4d pong;

    pong = {pongPos.at(0), pongPos.at(1), 0, 1};

    Eigen::Vector4d rob = H_Inv * pong;

    std::cout << rob << std::endl;

    std::vector<double> robPose;

    for (unsigned int i = 0; i < 3; ++i) {
        robPose.push_back((rob(i)/1000));
    }

    for (unsigned int i = 3; i < 6; ++i) {
       robPose.push_back(startPos.at(i));
    }

    rc.moveL(robPose);

}

void RobotController::moveDown(double down) {
    std::vector<double> TCP = rr.getActualTCPPose();
    TCP.at(5) = 0;

    TCP.at(2) = TCP.at(2) - down;

    rc.moveL(TCP);
}

void RobotController::moveUp(double up) {
    std::vector<double> TCP = rr.getActualTCPPose();
    TCP.at(5) = 0;

    TCP.at(2) = TCP.at(2) + up;

    rc.moveL(TCP);

}

void RobotController::throwPose() {

}







