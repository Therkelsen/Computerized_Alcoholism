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

    ///////////////Initial Velocity Angle//////////////////////7

    x = sqrt(pow(cup(0),2)+pow(cup(1),2));
    y = 0.277;
    mTime = t;
    Eigen::Vector2d xDirection(1,0);
    std::cout << "xDirection \n" << xDirection << "\n\n";
    std::vector<double> tcp = rc.getEndThrowPose();
    Eigen::Vector2d cup2d(cup(0)-tcp.at(0), cup(1)-tcp.at(1));
    std::cout << "cup2d \n" << cup2d << "\n\n";
    double taeller = xDirection(0)*cup2d(0)+xDirection(1)*cup2d(1);
    std::cout << "Tæller:\n";
    std::cout << taeller << "\n\n";
    double naevner = sqrt(pow(xDirection(0),2)+pow(xDirection(1),2))*sqrt(pow(cup2d(0),2)+pow(cup2d(1),2));
    std::cout << "Nævner:\n";
    std::cout << naevner << "\n\n";
    double toRad = /*(M_PI/2)-*/acos(taeller/naevner);

    std::cout << "ToRad \n" << toRad << "\n\n";

    angle = -toRad;


    double angleDegree = angle*180/M_PI;

    std::cout << "angleDegree: \n" << angleDegree << "\n\n" << std::endl;

    //////////////////////////////////////////////////////////////////////




    std::vector<double> temp = rc.getEndThrowPose();
    x0 = temp.at(0);
    y0 = temp.at(2);

    double v0x = (x-x0)/mTime;
    double v0y = (y-y0)/mTime+0.5*9.82*mTime;
    Eigen::Vector3d v0(v0x, 0, v0y);
    std::cout << "\nv0 : \n" << v0 << std::endl;
    Eigen::Matrix3d zRotation;
    zRotation << cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0,0,0,1;
    Eigen::Vector3d result = zRotation*v0;
    startV = result;
    std::cout << "Result: \n\n";
    std::cout << result << "\n\n" << std::endl;

    Eigen::VectorXd xDot(6);
    xDot << startV(0), startV(1), startV(2), 0, 0, 0;

    Eigen::MatrixXd jacobian(6,6);
    jacobian << 0.5788,   -0.0327,   -0.0062,   -0.0052,    0.2989,         0,
                0.2116,   -0.5002,   -0.0942,   -0.0796,    0.1202,         0,
                     0,   -0.5638,   -0.6867,   -0.2949,    0.0071,         0,
                     0,    0.9979,    0.9979,    0.9979,   -0.0033,    0.3737,
                     0,   -0.0652,   -0.0652,   -0.0652,   -0.0510,   -0.9264,
                1.0000,         0,         0,         0,    0.9987,   -0.0461;

                /*0.5825,    0.1336,    0.0280,    0.0229,    0.3043,         0,
                0.2917,   -0.5119,   -0.1074,   -0.0877,    0.1063,         0,
                     0,   -0.6373,   -0.7139,   -0.3224,    0.0003,         0,
                     0,    0.9676,    0.9676,    0.9676,    0.0032,    0.3297,
                     0,    0.2524,    0.2524,    0.2524,   -0.0122,   -0.9440,
                1.0000,         0,         0,         0,    0.9999,   -0.0126;


                0.6365,    0.0733,   -0.0049,   -0.0271,    0.3125,         0,
                0.2557,   -0.3917,    0.0260,    0.1446,    0.0772,         0,
                     0,   -0.6727,   -0.6739,   -0.3009,    0.0169,         0,
                     0,    0.9829,    0.9829,    0.9829,    0.1242,    0.2115,
                     0,    0.1840,    0.1840,    0.1840,   -0.6638,   -0.7085,
                1.0000,         0,         0,         0,    0.7375,   -0.6733;*/

    //    Eigen::MatrixXd jacobianInverse = jacobian.completeOrthogonalDecomposition().pseudoInverse();



    QDot.resize(6);
    QDot = jacobian.inverse() * xDot;

    std::cout << QDot << std::endl;

    accel = QDot/T;

    std::cout << "\n\naccel :\n"<< accel << std::endl;

    endJointPos.resize(6);
    double r = (abs(angleDegree) - 63.6) * 1.27;
    std::cout << "\n\nr : " << r << std::endl;
    double q6;
    if (abs(angleDegree) < 63.6) {
        q6 = -90 - abs(r);
    } else {
        q6 = -90 + abs(r);
    }

    std::cout << "\n\nq6 : " << q6 << std::endl;
    q6 = q6*M_PI/180;




    endJointPos << 1.51, -1.86, 1.83, -3.05, -1.12, q6;
                   //1.826, -1.752, 1.700, -3.077, -1.49, -1.571;
                   //1.6774, -1.8682, 1.8265, -1.8872, -1.4900, -1.8085;

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


std::vector<double> projectileMotion::getQDot() {
     std::vector<double> qd;

     for (unsigned int i = 0; i < 6; ++i) {
         qd.push_back(QDot(i));
     }

     return qd;
}

std::vector<double> projectileMotion::getAccel() {
    std::vector<double> a;

    for (unsigned int i = 0; i < 6; ++i) {
        a.push_back(accel(i));
    }

    return a;
}

double projectileMotion::getTEnd() {
    return T;
}

