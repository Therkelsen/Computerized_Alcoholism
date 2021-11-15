#ifndef CALIB_H
#define CALIB_H
#include "robotcontroller.h"
#include "machinevision.h"
#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <Eigen/Dense>
#include <Eigen/SVD>

class Calib
{
public:
    Calib(RobotController &rc, machineVision &mv, std::ostream &ost, std::istream &ist);
    Calib(); //Test-contructor: adds default values to member vectors pWorld & PRobot
    void printCoordinates(std::ostream &ost);
    void calcCentroids();
    void printCentroids(std::ostream &ost);
    void calcQ();
    void printQ(std::ostream &ost);
    void calcH();
    void printH();
    void calcSVD();
    void calcRot();
    void calcTrans();
    std::array<std::array<double, 3>, 3> getRot();
    std::array<double, 3> getTrans();
    void printCalibration();



private:
    std::vector<std::array<double, 3>> pWorld, PRobot, qWorld, QRobot;
    std::array<std::array<double, 3>, 3> H, V, U, Sum, R;
    std::array<double, 3> T, centroidR, centroidW;


};

#endif // CALIB_H
