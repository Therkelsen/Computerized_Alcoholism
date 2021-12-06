#ifndef PROJECTILEMOTION_H
#define PROJECTILEMOTION_H
#include <vector>
#include <Eigen/Dense>
#include "robotcontroller.h"

class projectileMotion
{
public:
    projectileMotion(Eigen::Vector4d cup, double t);
    void initialVelocity(RobotController &rc);
    void calcQDot();

private:
    std::vector<double> mBall, mCup;
    double x0, y0, x, y, angle;
    double mTime;
    Eigen::Vector3d startV;
    Eigen::VectorXd QDot;
};

#endif // PROJECTILEMOTION_H
