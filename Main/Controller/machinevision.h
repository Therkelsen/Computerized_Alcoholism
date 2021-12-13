#ifndef MACHINEVISION_H
#define MACHINEVISION_H
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pylon/PylonIncludes.h>

class machineVision
{
public:
    machineVision();
    std::vector<double> getBall();
    std::vector<double> getCup();
private:
    cv::Mat H;
};


#endif // MACHINEVISION_H
