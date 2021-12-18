#ifndef MACHINEVISION_H
#define MACHINEVISION_H
#include "database.h"
#include <vector>
#include <QString>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <pylon/PylonIncludes.h>

class machineVision {
public:
    int cellId;
    std::string cellIdString;
    machineVision(int cellId, QString cellIdString);
    std::vector<double> getBall();
    std::vector<double> getCup();
    std::vector<double> getIntrinsics(Database db);
    std::vector<double> getDistortionParams(Database db);
private:
    cv::Mat H;
};


#endif // MACHINEVISION_H
