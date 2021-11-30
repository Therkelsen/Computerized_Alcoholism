#ifndef PROJECTILEMOTION_H
#define PROJECTILEMOTION_H
#include <vector>

class projectileMotion
{
public:
    projectileMotion(std::vector<double> ball, std::vector<double> cup, int t);
    std::vector<double> initialVelocity();

private:
    std::vector<double> mBall, mCup;
    double x0, y0;
    int mTime;
};

#endif // PROJECTILEMOTION_H
