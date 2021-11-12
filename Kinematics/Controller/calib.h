#ifndef CALIB_H
#define CALIB_H
#include "robotcontroller.h"
#include "machinevision.h"
#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

class Calib
{
public:
    Calib(RobotController &rc, machineVision &mv, std::ostream &ost, std::istream &ist);
    void printCoordinates(std::ostream &ost);
    void calcCentroids();
    void calcQ();
    void calcH();
    void calcSVD();
    void calcRot();
    void calcTrans();



private:
    std::vector<std::array<double, 3>> pWorld, PRobot, qWorld, QRobot;
    double centroidR[3], centroidW[3];
    std::array<std::array<double, 3>, 3> H, V, U, Sum, R, T;


};

#endif // CALIB_H
