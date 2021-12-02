#include "projectilemotion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

projectileMotion::projectileMotion(Eigen::Vector4d cup, double t)
{
    double x =sqrt(pow(cup(0),2)+pow(cup(1),2));
    double y = 0.277;
    double x0;
    double y0;
    mTime = t;
    Eigen::Vector2d xDirection(1,0);
    Eigen::Vector2d cup2d(cup(0), cup(1));
    double taeller = xDirection(0)*cup2d(0)+xDirection(1)*cup2d(1);
    double naevner = sqrt(pow(xDirection(0),2)+pow(xDirection(1),2))+sqrt(pow(xDirection(0),2)+pow(xDirection(1),2));

    double angle = acos(taeller/naevner);
}

Eigen::Vector3d projectileMotion::initialVelocity(RobotController &rc)
{
    std::vector<double> temp = rc.getEndThrowPose();
    x0 = temp.at(0);
    y0 = temp.at(2);



    double v0x = (x-x0)/mTime;
    double v0y = (y-y0)/mTime+0.5*9.82*mTime;
    Eigen::Vector3d v0(v0x, 0, v0y);
    Eigen::Matrix3d zRotation;
    zRotation << cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0,0,0,1;
    Eigen::Vector3d result = zRotation*v0;
    return result;
}
