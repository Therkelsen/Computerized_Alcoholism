
/*
*  Class implementation of ur_rtde library @ https://sdurobotics.gitlab.io/ur_rtde/index.html
*  Created November 3rd, 2021
*  Authored by Thomas Therkelsen @ SDU
*/

#include "robotcontroller.h"



RobotController::RobotController(const std::string ipAddress, std::vector<double> &startingPos)
  :rc(ipAddress), startPos(startingPos) {
  std::cout << std::boolalpha;

  ip = ipAddress;
}

void RobotController::startingPos() {
    // Send robot to base position
    rc.moveL(startPos);
}

std::array<double, 3> RobotController::getTCP() {
    ur_rtde::RTDEReceiveInterface rr(ip);

    std::vector<double> TCP = rr.getActualTCPPose();
    //rr.~RTDEReceiveInterface();

    std::array<double, 3> TCPPose;

    //Copies TCP and converts to mm

    for (unsigned int i = 0; i < 3; ++i) {
        TCPPose.at(i) = TCP.at(i) * 1000;
    }



    return TCPPose;

}

void RobotController::setR() {

    R(0,0) = 46.0;
    R(0,1) = -0.79;
    R(0,2) = 0.41;
    R(1,0) = 0.84;
    R(1,1) = 0.54;
    R(1,2) = 0.11;
    R(2,0) = 0.30;
    R(2,1) = -0.30;
    R(2,2) = -0.91;
}

void RobotController::setT() {
    T = {-217.20, 332.90, -33.47};

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

void RobotController::moveToPong(/*machineVision &mv*/)  {
    //pongPos = mv.getObject(1);

    pongPos = {174.43, 270.46};

    Eigen::Vector4d pong;

    pong = {pongPos.at(0), pongPos.at(1), 0, 1};

    //test udskrivning af pong
    std::cout << "Pong: \n";
    for (unsigned int i = 0; i < 4; ++i) {
        std::cout << pong(i) << " ";
    }
    std::cout << "\n";



    Eigen::Vector4d rob = H_Inv * pong;

    std::cout << rob << std::endl;

}









