#include "projectilemotion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

projectileMotion::projectileMotion(std::vector<double> ball, std::vector<double> cup, int t)
{
    mBall = ball;
    mCup = cup;
    double x0 = 0;
    double y0 = 0;
    mTime = t;
}

std::vector<double> projectileMotion::initialVelocity()
{
    double v0x = (mBall[0]-x0)/mTime;
    double v0z = (mBall[1]-y0)/mTime+0.5*9.82*mTime;
    double v0Array[3] = {v0x, 0, v0z};
    cv::Mat v0(3,1,CV_32F, v0Array);
    double angle = 45*M_PI/180;
    double rotation[9] = {cos(angle), -sin(angle),0,sin(angle),cos(angle),0,0,0,1};
    cv::Mat zRotation(3,3,CV_32F, rotation);
    cv::Mat result = v0*zRotation;

    std::vector<double> resultVector = {result.at<double>(0,0), result.at<double>(1,0), result.at<double>(2,0)};
    return resultVector;
}
