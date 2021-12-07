#include "projectilemotion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

projectileMotion::projectileMotion() {

}

std::vector<double> projectileMotion::getStartThrowPos(Eigen::Vector4d cup, double t, RobotController &rc) {
    x = sqrt(pow(cup(0),2)+pow(cup(1),2));
    y = 0.277;
    mTime = t;
    Eigen::Vector2d xDirection(1,0);
    std::cout << "xDirection \n" << xDirection << "\n\n";
    Eigen::Vector2d cup2d(cup(0), cup(1));
    std::cout << "cup2d \n" << cup2d << "\n\n";
    double taeller = xDirection(0)*cup2d(0)+xDirection(1)*cup2d(1);
    std::cout << "Tæller:\n";
    std::cout << taeller << "\n\n";
    double naevner = sqrt(pow(xDirection(0),2)+pow(xDirection(1),2))*sqrt(pow(cup2d(0),2)+pow(cup2d(1),2));
    std::cout << "Nævner:\n";
    std::cout << naevner << "\n\n";
    double toRad = acos(taeller/naevner);

    std::cout << "ToRad \n" << toRad << "\n\n";

    angle = toRad;


    double angleDegree = angle*180/M_PI;

    std::cout << "angleDegree: \n" << angleDegree << "\n\n" << std::endl;

    std::vector<double> temp = rc.getEndThrowPose();
    x0 = temp.at(0);
    y0 = temp.at(2);

    double v0x = (x-x0)/mTime;
    double v0y = (y-y0)/mTime+0.5*9.82*mTime;
    Eigen::Vector3d v0(v0x, 0, v0y);
    Eigen::Matrix3d zRotation;
    zRotation << cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0,0,0,1;
    Eigen::Vector3d result = zRotation*v0;
    startV = result;
    std::cout << "Result: \n\n";
    std::cout << result << "\n\n" << std::endl;

    Eigen::VectorXd xDot(6);
    xDot << startV(0), startV(1), startV(2), 0, 0, 0;

    Eigen::MatrixXd jacobian(6,6);
    jacobian << 0.4514, 0.0165, -0.0268, -0.0285, 0.3185, 0,
                0.1843, -0.1541, 0.2499, 0.2661, 0.0433, 0,
                     0, -0.4684, -0.5930, -0.2013, 0.0244, 0,
                     0, 0.9943, 0.9943, 0.9943, 0.0997, 0.1175,
                     0, 0.1064, 0.1064, 0.1064, -0.9312, -0.3388,
                1.0000, 0, 0, 0, 0.3505, -0.9335;

    QDot.resize(6);
    QDot = jacobian.inverse() * xDot;

    std::cout << QDot << std::endl;

    accel = QDot/T;

    std::cout << "\n\naccel :\n"<< accel << std::endl;

    endJointPos.resize(6);
    endJointPos << 1.6774, -1.8682, 1.8265, -1.8872, -1.4900, -1.8085;

    std::cout << "\n endJointPos: \n" << endJointPos << std::endl;

    startJointPos.resize(6);
    for (unsigned int i = 0; i < 6; ++i) {
        startJointPos(i) = endJointPos(i) - (accel(i)/2)*pow(T,2);
    }
    std::cout << "\nStartJointPos :\n" << startJointPos << std::endl;

    std::vector<double> startThrowPos;

    for (unsigned int i = 0; i < 6; ++i) {
        startThrowPos.push_back(startJointPos(i));
    }

    return startThrowPos;
}

