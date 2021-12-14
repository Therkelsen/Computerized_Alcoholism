#ifndef PROJECTILEMOTION_H
#define PROJECTILEMOTION_H
#include <vector>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "robotcontroller.h"

class projectileMotion
{
public:
    projectileMotion();
    std::vector<double> getStartThrowPos(Eigen::Vector4d cup, double t, RobotController &rc);
    std::vector<double> getQDot();
    std::vector<double> getAccel();
    double getTEnd();


private:
    std::vector<double> mBall, mCup;
    double x0, y0, x, y, angle;
    double mTime;
    double T = 0.16;
    Eigen::Vector3d startV;
    Eigen::VectorXd QDot, accel, endJointPos, startJointPos;

};

#endif // PROJECTILEMOTION_H
