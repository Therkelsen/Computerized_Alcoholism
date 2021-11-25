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
    void convertToEigen();
    void calcCentroids();
    void calcQ();
    void calcH();
    void calcSVD();
    void calcRot();
    void calcTrans();
    void getRot();
    void printCalibration();



private:
    std::vector<std::array<double, 3>> pWorldArr, PRobotArr;
    Eigen::MatrixX3d pWorld, PRobot, qWorld, QRobot;
    Eigen::Vector3d centroidR, centroidW, T;
    Eigen::Matrix3d H, U, V, R;



};

#endif // CALIB_H
