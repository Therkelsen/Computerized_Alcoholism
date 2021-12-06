#include "projectilemotion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

projectileMotion::projectileMotion(Eigen::Vector4d cup, double t)
{
    x = sqrt(pow(cup(0),2)+pow(cup(1),2));
    y = 0.277;
    mTime = t;
    Eigen::Vector2d xDirection(1,0);
    std::cout << xDirection << "\n\n";
    Eigen::Vector2d cup2d(cup(0), cup(1));
    std::cout << cup2d << "\n\n";
    double taeller = xDirection(0)*cup2d(0)+xDirection(1)*cup2d(1);
    std::cout << "Tæller:\n";
    std::cout << taeller << "\n\n";
    double naevner = sqrt(pow(xDirection(0),2)+pow(xDirection(1),2))+sqrt(pow(xDirection(0),2)+pow(xDirection(1),2));
    std::cout << "Nævner:\n";
    std::cout << naevner << "\n\n";
    double toRad = (taeller/naevner)*(M_PI/180);

    std::cout << toRad << "\n\n";

    double radAngle = acos(toRad);
    angle = (radAngle*180) /M_PI;


    std::cout << angle << "\n\n";
}

void projectileMotion::initialVelocity(RobotController &rc)
{
    std::cout << "fisse";
    std::vector<double> temp = rc.getEndThrowPose();
    x0 = temp.at(0);
    y0 = temp.at(2);

    std::cout << "FIsse";

    double v0x = (x-x0)/mTime;
    double v0y = (y-y0)/mTime+0.5*9.82*mTime;
    Eigen::Vector3d v0(v0x, 0, v0y);
    Eigen::Matrix3d zRotation;
    zRotation << cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0,0,0,1;
    Eigen::Vector3d result = zRotation*v0;
    startV = result;

}

void projectileMotion::calcQDot() {

    Eigen::RowVectorXd xDot(6);
    xDot << startV(0), startV(1), startV(2), 0, 0, 0;

    Eigen::MatrixXd jacobian(6,6);
    jacobian << 0.0150, 0.0098, -0.0384, -0.0543, -0.1857, 0,
            -0.1689, -0.0326, 0.1281, 0.1811, 0.0356, 0,
            0, 0.0341, 0.4246, 0.0365, 0.2610, 0,
            0, 0.9578, 0.9578, 0.9578, -0.2724, -0.7706,
            0, 0.2873, 0.2873, 0.2873, 0.9082, -0.4037,
            1.0000, 0, 0, 0, -0.3178, -0.4932;

    QDot.resize(6);
    QDot = jacobian.inverse() * xDot;

    std::cout << QDot;



}
