#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <array>
#include <vector>
#include <filesystem>

int main(int argc, char **argv) {

    (void)argc;
    (void)argv;

    std::vector<cv::String> fileNames;
    cv::glob("../Calibration/images/*.png", fileNames, false);
    cv::Size patternSize(10 - 1, 7 - 1);
    std::vector<std::vector<cv::Point2f>> q(fileNames.size());

    // Detect feature points
    std::size_t i = 0;
    for (auto const &f : fileNames) {
        std::cout << std::string(f) << std::endl;

        // 1. Read in the image an call cv::findChessboardCorners()
        cv::Mat img = cv::imread(fileNames[i], cv::IMREAD_GRAYSCALE);
        cv::Mat imgBGR = cv::imread(fileNames[i]);

        bool success = cv::findChessboardCorners(img, patternSize, q[i]);

        // 2. Use cv::cornerSubPix() to refine the found corner detections
        cv::TermCriteria tCriteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, 0.0001);
        cv::cornerSubPix(img, q[i], cv::Size(11,11), cv::Size(-1,-1), tCriteria);

        // Display
        cv::drawChessboardCorners(imgBGR, patternSize, q[i], success);
        cv::imshow("chessboard detection", imgBGR);
        cv::waitKey(0);
        //std::cout << q[i] << std::endl;

        i++;
    }

    std::vector<std::vector<cv::Point3f>> Q;
    // 3. Generate checkerboard (world) coordinates Q. The board has 10 x 7
    // fields with a size of 70x70mm
    int boardSize[2] = {10-1, 7-1};
    std::vector<cv::Point3f> temp;
    for (int i = 0; i < boardSize[0]; i++){
        for (int j = 0; j < boardSize[1]; j++ ){
            temp.push_back(cv::Point3f(float(i*70), float(j*70), 0.0f));
        }
    }
    for (int i = 0; i < q.size(); i++){
        Q.push_back(temp);
    }


    cv::Matx33f K(cv::Matx33f::eye());  // intrinsic camera matrix
    cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients

    std::vector<cv::Mat> rvecs, tvecs;
    std::vector<double> stdIntrinsics, stdExtrinsics, perViewErrors;
    cv::Size frameSize(1440, 1080);

    std::cout << "Calibrating..." << std::endl;
    // 4. Call "float error = cv::calibrateCamera()" with the input coordinates
    // and output parameters as declared above...

    float error = cv::calibrateCamera(Q,q,frameSize,K,k,rvecs,tvecs,
                                      stdIntrinsics,stdExtrinsics,perViewErrors);

    std::cout << "Reprojection error = " << error << "\nK =\n"
            << K << "\nk=\n"
            << k << std::endl;

    // Precompute lens correction interpolation
    cv::Mat mapX, mapY;
    cv::initUndistortRectifyMap(K, k, cv::Matx33f::eye(), K, frameSize, CV_32FC1,
                                mapX, mapY);

    // Show lens corrected images
    for (auto const &f : fileNames) {
        std::cout << std::string(f) << std::endl;

        cv::Mat img = cv::imread(f, cv::IMREAD_COLOR);

        cv::Mat imgUndistorted;
        // 5. Remap the image using the precomputed interpolation maps.
        cv::remap(img, imgUndistorted, mapX, mapY,cv::INTER_LINEAR, cv::BORDER_REPLICATE);

        // Display
        cv::imshow("undistorted image", imgUndistorted);
        cv::waitKey(0);
    }

    return 0;
}
