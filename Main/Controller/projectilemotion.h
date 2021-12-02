#ifndef PROJECTILEMOTION_H
#define PROJECTILEMOTION_H
#include <vector>
#include <Eigen/Dense>
#include "robotcontroller.h"

class projectileMotion
{
public:
    projectileMotion(Eigen::Vector4d cup, double t);
    Eigen::Vector3d initialVelocity(RobotController &rc);

private:
    std::vector<double> mBall, mCup;
    double x0, y0, x, y, angle;
    int mTime;
};

#endif // PROJECTILEMOTION_H
