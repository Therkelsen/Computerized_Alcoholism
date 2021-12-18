
/*
*  Class implementation of ur_rtde library @ https://sdurobotics.gitlab.io/ur_rtde/index.html
*  Created November 3rd, 2021
*  Authored by Thomas Therkelsen @ SDU
*/

#include "robotcontroller.h"
#include "projectilemotion.h"


RobotController::RobotController(const std::string ipAddress, const std::string gripIP)
  :rc(ipAddress), rr(ipAddress), gc(gripIP), db(){
  std::cout << std::boolalpha;
  gc.open();
  gc.start();
  ip = ipAddress;
  gripperIP = gripIP;
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
    std::vector<double> rotation = db.extractRotation(QString::fromStdString(cellIdString));

    R(0,0) = rotation.at(0);
    R(0,1) = rotation.at(1);
    R(0,2) = rotation.at(2);
    R(1,0) = rotation.at(3);
    R(1,1) = rotation.at(4);
    R(1,2) = rotation.at(5);
    R(2,0) = rotation.at(6);
    R(2,1) = rotation.at(7);
    R(2,2) = rotation.at(8);
}

void RobotController::setT() {
    std::vector<double> translation = db.extractTranslation(QString::fromStdString(cellIdString));
    T = {translation.at(0), translation.at(1), translation.at(2)};
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

   /* std::cout << "\n\nH: ";
    for (unsigned int i = 0; i < 4; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 4; ++j) {
            std::cout << H(i,j) << " ";
        }
    }
    std::cout << "\n";
    */

    H_Inv = H.inverse();

    //testudskrivning af H_Inv
   /* std::cout << "H_Inv : \n";
    for (unsigned int i = 0; i < 4; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 4; ++j) {
            std::cout << H_Inv(i,j) << " ";
        }
    }

    std::cout << "\n";
*/

}

void RobotController::moveToPong(machineVision &mv)  {
    pongPos = mv.getBall();

    Eigen::Vector4d pong;

    pong = {pongPos.at(0), pongPos.at(1), 0, 1};

    Eigen::Vector4d rob = H_Inv * pong;

    std::cout << "Rob : \n "<< rob << std::endl;

    std::vector<double> robPose;

    for (unsigned int i = 0; i < 3; ++i) {
        robPose.push_back((rob(i)/1000));
    }

    for (unsigned int i = 3; i < 6; ++i) {
       robPose.push_back(startPos.at(i));
    }

    rc.moveL(robPose);

}

Eigen::Vector4d RobotController::getRobCoords(machineVision &mv) {
    std::vector<double> cupPos = mv.getCup();

    Eigen::Vector4d cup;

    cup = {cupPos.at(0), cupPos.at(1), 0, 1};

    Eigen::Vector4d temp = H_Inv * cup;
    Eigen::Vector4d robCoords = temp/1000;



    return robCoords;
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

void RobotController::startThrowPose(std::vector<double> startThrowPos) {
    rc.moveL_FK(startThrowPos);
    std::cout << "StartThowPos : \n";

    for (unsigned int i  = 0; i < startThrowPos.size(); ++i) {
        std::cout << startThrowPos.at(i) << std::endl;
    }


}

std::vector<double> RobotController::getEndThrowPose() {
    std::vector<double> endPose;

    for (unsigned int i = 0; i < 3; i++) {
        endPose.push_back(endThrowPos.at(i));
    }

    return endPose;
}

void RobotController::grip() {

    gc.doPrePositionFingers(0.04f, 0.2f);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}


void RobotController::releaseGrip(double T) {
    int temp = static_cast<int>(T*1000);
    int offset = 30;
    std::this_thread::sleep_for(std::chrono::milliseconds(temp-offset));

    gc.doPrePositionFingers(0.1f, 0.4f);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}

void RobotController::stopGripper() {
    gc.stop();
    gc.close();
}

void RobotController::throwPong(std::vector<double> QDot, std::vector<double> Accel, double T) {
    double max = 0;
    for(int i = 0; i < Accel.size(); i++){
        if(abs(max) < abs(Accel.at(i))){
            max = abs(Accel.at(i));
        }
    }
    std::cout << "max accel" <<  std::endl;
    std::cout << max << std::endl;
    rc.speedJ(QDot, 40);
}

void RobotController::stopThrow() {
    rc.speedStop(40);
}
