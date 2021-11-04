#include "robotcontroller.h"

RobotController::RobotController(const std::string ipAddress, std::vector<double> &startingPos)
    :rc(ipAddress), startPos(startingPos){}

void RobotController::StartingPos() {
    double rad = M_PI/180;

    // Send robot to base position
    // (const std::vector<double> &q, double speed = 1.05, double acceleration = 1.4, bool async = false)

    std::cout << "UR_RTDE: Sending joint pose to Robot using moveJ" << std::endl;
    std::cout << "         Start pos [rad]: (";

    for (int i = 0; i < startPos.size(); i++) {
        if (i < startPos.size()-1) {
            std::cout << startPos.at(i) << ", ";
        } else {
            std::cout << startPos.at(i) << ")" << std::endl;
        }
    }

    std::cout << "         Speed [unit]: " << speed;
    std::cout << "\n         Acceleration [unit]: " << accel;
    std::cout << "\n         Async: " << async << "\n" << std::endl;

    rc.moveL(startPos, speed, accel, async);

}

void RobotController::setPongPos(std::vector<double> &pongCoordinates) {

    pongPos = pongCoordinates;
}

void RobotController::setRobToPong() {

    robToPong{pongPos.at(0) - 850, pongPos.at(1) - 300};

}

void RobotController::moveToPong() {

    rc.moveL(abovePong, speed, accel, async);

}

void RobotController::gripAndLift() {
    // Her indsættes noget IO-kode for at åbne gripperen

    /_________________________________________________/

    //Gripperen sænkes ned over bolden
    rc.moveL(atPong, speed, accel, async);


    // Her indsættes IO-kode som lukker gripperen

    /_____________________________________________/


    //Bolden løftes op
    rc.moveL(abovePong, speed, accel, async);

}









