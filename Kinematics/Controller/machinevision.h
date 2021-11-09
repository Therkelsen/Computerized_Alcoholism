#ifndef MACHINEVISION_H
#define MACHINEVISION_H
#include <vector>
#include <pylon/PylonIncludes.h>

class machineVision
{
public:
    machineVision();
    std::vector<double> getObject(bool getBall);

private:
    Pylon::CInstantCamera camera;
};


#endif // MACHINEVISION_H
