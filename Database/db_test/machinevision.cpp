#include "machinevision.h"

machineVision::machineVision(int cellId, QString cellIdString){
    this->cellId = cellId;
    this->cellIdString = cellIdString.toUtf8().constData();

    // Homography
    cv::Point2f imagePoints[4];
    cv::Point2f tablePoints[4];

    Database db;
    std::vector<double> imagePointss = db.extractImagePoints(cellIdString);
    /*imagePoints[0] = cv::Point2f(488.5, 1018.5);
    imagePoints[1] = cv::Point2f(486.5, 462.5);
    imagePoints[2] = cv::Point2f(1046.5, 459.5);
    imagePoints[3] = cv::Point2f(1049.5, 1026.5);*/
    imagePoints[0] = cv::Point2f(imagePointss.at(0), imagePointss.at(1));
    imagePoints[1] = cv::Point2f(imagePointss.at(2), imagePointss.at(3));
    imagePoints[2] = cv::Point2f(imagePointss.at(4), imagePointss.at(5));
    imagePoints[3] = cv::Point2f(imagePointss.at(6), imagePointss.at(7));

    tablePoints[0] = cv::Point2f(0, 650);
    tablePoints[1] = cv::Point2f(0, 0);
    tablePoints[2] = cv::Point2f(650, 0);
    tablePoints[3] = cv::Point2f(650, 650);

    H = cv::getPerspectiveTransform(imagePoints, tablePoints, cv::DECOMP_LU);
}

std::vector<double> machineVision::getBall()
{
    int myExposure = 30000;
    // The exit code of the sample application.
    int exitCode = 0;

    // Automagically call PylonInitialize and PylonTerminate to ensure the pylon runtime system
    // is initialized during the lifetime of this object.
    Pylon::PylonAutoInitTerm autoInitTerm;
    std::vector<double> tableCoordinatesInhomo;
    try
    {
        // Create an instant camera object with the camera device found first.
        Pylon::CInstantCamera camera( Pylon::CTlFactory::GetInstance().CreateFirstDevice());

        // Get a camera nodemap in order to access camera parameters.
        GenApi::INodeMap& nodemap= camera.GetNodeMap();

        // Open the camera before accessing any parameters.
        camera.Open();
        // Create pointers to access the camera Width and Height parameters.
        GenApi::CIntegerPtr width= nodemap.GetNode("Width");
        GenApi::CIntegerPtr height= nodemap.GetNode("Height");

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        //camera.MaxNumBuffer = 5;

        // Create a pylon ImageFormatConverter object.
        Pylon::CImageFormatConverter formatConverter;
        // Specify the output pixel format.
        formatConverter.OutputPixelFormat= Pylon::PixelType_BGR8packed;
        // Create a PylonImage that will be used to create OpenCV images later.
        Pylon::CPylonImage pylonImage;

        // Create an OpenCV image.
        cv::Mat openCvImage;


        // Set exposure to manual
        GenApi::CEnumerationPtr exposureAuto( nodemap.GetNode( "ExposureAuto"));
        if ( GenApi::IsWritable( exposureAuto)){
            exposureAuto->FromString("Off");
            // std::cout << "Exposure auto disabled." << std::endl;
        }

        // Set custom exposure
        GenApi::CFloatPtr exposureTime = nodemap.GetNode("ExposureTime");
        // std::cout << "Old exposure: " << exposureTime->GetValue() << std::endl;
        if(exposureTime.IsValid()) {
            if(myExposure >= exposureTime->GetMin() && myExposure <= exposureTime->GetMax()) {
                exposureTime->SetValue(myExposure);
            }else {
                exposureTime->SetValue(exposureTime->GetMin());
                std::cout << ">> Exposure has been set with the minimum available value." << std::endl;
                std::cout << ">> The available exposure range is [" << exposureTime->GetMin() << " - " << exposureTime->GetMax() << "] (us)" << std::endl;
            }
        }else {

            std::cout << ">> Failed to set exposure value." << std::endl;
            //return false;
        }
        //std::cout << "New exposure: " << exposureTime->GetValue() << std::endl;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);

        // This smart pointer will receive the grab result data.
        Pylon::CGrabResultPtr ptrGrabResult;

        // image grabbing loop
        int frame = 1;
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;

                // Convert the grabbed buffer to a pylon image.
                formatConverter.Convert(pylonImage, ptrGrabResult);

                // Create an OpenCV image from a pylon image.
                openCvImage= cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

                //////////////////////////////////////////////////////
                //////////// Here your code begins ///////////////////
                //////////////////////////////////////////////////////

                // Create an OpenCV display window.
                //cv::namedWindow( "myWindow", cv::WINDOW_NORMAL); // other options: CV_AUTOSIZE, CV_FREERATIO

                // Display the current image in the OpenCV display window.
                //cv::imshow( "myWindow", openCvImage);
                int keyPressed = cv::waitKey(1);
                // Detect key press and quit if 'q' is pressed
                if(keyPressed == 'q') { //quit
                    std::cout << "Shutting down camera..." << std::endl;
                    camera.Close();
                    std::cout << "Camera successfully closed." << std::endl;
                    break;
                }

                //if(keyPressed == ' '){ //take picture
                std::cout << "Taking picture..." << std::endl;
                //float data[9] = {443.30481, 0, 719.5, 0, 471.87396, 539.5, 0, 0, 1};
                float data[9];
                Database db;
                std::vector<double> intrinsics = db.extractIntrinsics(cellId);
                for (int i = 0; i < intrinsics.size(); i++) {
                    data[i] = intrinsics.at(i);
                }
                cv::Mat K(3,3,CV_32F,data);  // intrinsic camera matrix

                std::vector<double> distortionParams = db.extractDistortionParameters(cellId);
                cv::Vec<float, 5> k(distortionParams.at(0), distortionParams.at(1), distortionParams.at(2), distortionParams.at(3), distortionParams.at(4)); // distortion coefficients
                //cv::Vec<float, 5> k(-0.0306633, 0.000208614, 0.000163452, -0.00413883, -3.86967e-07); // distortion coefficients
                cv::Mat undistortedImg;
                cv::undistort(openCvImage, undistortedImg, K, k);

                cv::Mat output;

                //std::cout << "Homography matrix:" << std::endl;
                //std::cout << H << std::endl;

                cv::warpPerspective(undistortedImg, output, H, output.size());
                //cv::imshow("output", output);

                //Convert to grayscale
                cv::Mat gray;
                cv::cvtColor(undistortedImg, gray, cv::COLOR_BGR2GRAY);
                cv::medianBlur(gray, gray, 5);

                std::vector<cv::Vec3f> circles;
                std::vector<cv::Vec3f> balls;
                cv::Vec3f ball;
                cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows/16, 60, 30, 15, 40);
                for (int i = 0; i < circles.size(); i++) {
                    //std::cout << "Detected circle:" << std::endl;
                    cv::Vec3f temp = circles[i];
                    //std::cout << temp << std::endl;
                    if(temp[2] < 20 && temp[0] < 1100 && temp[0] > 450 && temp[1] < 1100 && temp[1] > 430){
                        temp[2] = 1;
                        balls.push_back(temp);
                    }
                }

                try{
                    if(balls.size() == 1){
                        ball = balls[0];
                    }
                    else{
                        int numberOfBalls = balls.size();
                        throw(numberOfBalls);
                    }
                }
                catch(int numberOfBalls){
                    std::cout << "Error. Incorrect number of balls" << std::endl;
                    std::cout << "Number of balls found: " << numberOfBalls << std::endl;
                    // Display the image with found circles
                    for (int i = 0; i < circles.size(); i++) {
                        cv::Vec3i c = circles[i];
                        cv::Point center = cv::Point(c[0], c[1]);
                        //circle center
                        circle(undistortedImg, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
                        //circle outline
                        int radius = c[2];
                        circle(undistortedImg, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
                    }

                    cv::imshow("Detected circles", undistortedImg);
                    cv::waitKey(0);
                    //std::cout << "Shutting down camera..." << std::endl;
                    camera.Close();
                    //std::cout << "Camera successfully closed." << std::endl;
                    break;
                }

                cv::Mat ballMat = cv::Mat(ball);
                ballMat.convertTo(ballMat, CV_64F);

                cv::Mat tableCoordinatesHomo;
                tableCoordinatesHomo = H * ballMat;

                tableCoordinatesInhomo = {tableCoordinatesHomo.at<double>(1,0)/tableCoordinatesHomo.at<double>(2,0),
                                          tableCoordinatesHomo.at<double>(0,0)/tableCoordinatesHomo.at<double>(2,0)};

                // Display the image with found circles
                for (int i = 0; i < circles.size(); i++) {
                    cv::Vec3i c = circles[i];
                    cv::Point center = cv::Point(c[0], c[1]);
                    //circle center
                    circle(undistortedImg, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
                    //circle outline
                    int radius = c[2];
                    circle(undistortedImg, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
                }

                //cv::imshow("Detected circles", undistortedImg);
                //cv::waitKey(0);
                //std::cout << "Shutting down camera..." << std::endl;
                camera.Close();
                //std::cout << "Camera successfully closed." << std::endl;
                break;
                //}

                ////////////////////////////////////////////////////
                //////////// Here your code ends ///////////////////
                ////////////////////////////////////////////////////

                frame++;

            }
            else
            {
                std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
            }
        }

    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl
                  << e.GetDescription() << std::endl;
        exitCode = 1;
    }

    return tableCoordinatesInhomo;
}

std::vector<double> machineVision::getCup()
{
    int myExposure = 30000;
    // The exit code of the sample application.
    int exitCode = 0;

    // Automagically call PylonInitialize and PylonTerminate to ensure the pylon runtime system
    // is initialized during the lifetime of this object.
    Pylon::PylonAutoInitTerm autoInitTerm;
    std::vector<double> tableCoordinatesInhomo;
    try
    {
        // Create an instant camera object with the camera device found first.
        Pylon::CInstantCamera camera( Pylon::CTlFactory::GetInstance().CreateFirstDevice());

        // Get a camera nodemap in order to access camera parameters.
        GenApi::INodeMap& nodemap= camera.GetNodeMap();

        // Open the camera before accessing any parameters.
        camera.Open();
        // Create pointers to access the camera Width and Height parameters.
        GenApi::CIntegerPtr width= nodemap.GetNode("Width");
        GenApi::CIntegerPtr height= nodemap.GetNode("Height");

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        //camera.MaxNumBuffer = 5;

        // Create a pylon ImageFormatConverter object.
        Pylon::CImageFormatConverter formatConverter;
        // Specify the output pixel format.
        formatConverter.OutputPixelFormat= Pylon::PixelType_BGR8packed;
        // Create a PylonImage that will be used to create OpenCV images later.
        Pylon::CPylonImage pylonImage;

        // Create an OpenCV image.
        cv::Mat openCvImage;

        // Set exposure to manual
        GenApi::CEnumerationPtr exposureAuto( nodemap.GetNode( "ExposureAuto"));
        if ( GenApi::IsWritable( exposureAuto)){
            exposureAuto->FromString("Off");
            // std::cout << "Exposure auto disabled." << std::endl;
        }

        // Set custom exposure
        GenApi::CFloatPtr exposureTime = nodemap.GetNode("ExposureTime");
        // std::cout << "Old exposure: " << exposureTime->GetValue() << std::endl;
        if(exposureTime.IsValid()) {
            if(myExposure >= exposureTime->GetMin() && myExposure <= exposureTime->GetMax()) {
                exposureTime->SetValue(myExposure);
            }else {
                exposureTime->SetValue(exposureTime->GetMin());
                std::cout << ">> Exposure has been set with the minimum available value." << std::endl;
                std::cout << ">> The available exposure range is [" << exposureTime->GetMin() << " - " << exposureTime->GetMax() << "] (us)" << std::endl;
            }
        }else {

            std::cout << ">> Failed to set exposure value." << std::endl;
            //return false;
        }
        //std::cout << "New exposure: " << exposureTime->GetValue() << std::endl;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);

        // This smart pointer will receive the grab result data.
        Pylon::CGrabResultPtr ptrGrabResult;

        // image grabbing loop
        int frame = 1;
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;

                // Convert the grabbed buffer to a pylon image.
                formatConverter.Convert(pylonImage, ptrGrabResult);

                // Create an OpenCV image from a pylon image.
                openCvImage= cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

                //////////////////////////////////////////////////////
                //////////// Here your code begins ///////////////////
                //////////////////////////////////////////////////////

                // Create an OpenCV display window.
                //cv::namedWindow( "myWindow", cv::WINDOW_NORMAL); // other options: CV_AUTOSIZE, CV_FREERATIO

                // Display the current image in the OpenCV display window.
                //cv::imshow( "myWindow", openCvImage);
                int keyPressed = cv::waitKey(1);
                // Detect key press and quit if 'q' is pressed
                if(keyPressed == 'q') { //quit
                    std::cout << "Shutting down camera..." << std::endl;
                    camera.Close();
                    std::cout << "Camera successfully closed." << std::endl;
                    break;
                }

                //if(keyPressed == ' '){ //take picture
                std::cout << "Taking picture..." << std::endl;

                //float data[9] = {443.30481, 0, 719.5, 0, 471.87396, 539.5, 0, 0, 1};
                float data[9];
                Database db;
                std::vector<double> intrinsics = db.extractIntrinsics(cellId);
                for (int i = 0; i < intrinsics.size(); i++) {
                    data[i] = intrinsics.at(i);
                }
                cv::Mat K(3,3,CV_32F,data);  // intrinsic camera matrix

                std::vector<double> distortionParams = db.extractDistortionParameters(cellId);
                cv::Vec<float, 5> k(distortionParams.at(0), distortionParams.at(1), distortionParams.at(2), distortionParams.at(3), distortionParams.at(4)); // distortion coefficients
                //cv::Vec<float, 5> k(-0.0306633, 0.000208614, 0.000163452, -0.00413883, -3.86967e-07); // distortion coefficients

                cv::Mat undistortedImg;
                cv::undistort(openCvImage, undistortedImg, K, k);

                cv::Mat output;

                //std::cout << "Homography matrix:" << std::endl;
                //std::cout << H << std::endl;

                cv::warpPerspective(undistortedImg, output, H, output.size());
                //cv::imshow("output", output);

                //Convert to grayscale
                cv::Mat gray;
                cv::cvtColor(undistortedImg, gray, cv::COLOR_BGR2GRAY);
                cv::medianBlur(gray, gray, 5);

                std::vector<cv::Vec3f> circles;
                std::vector<cv::Vec3f> cups;
                cv::Vec3f cup;
                cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows/16, 60, 30, 15, 40);
                for (int i = 0; i < circles.size(); i++) {
                    //std::cout << "Detected circle:" << std::endl;
                    cv::Vec3f temp = circles[i];
                    //std::cout << temp << std::endl;
                    if(temp[2] > 19){
                        temp[2] = 1;
                        cups.push_back(temp);
                    }
                }
                cup = cups[0];
                cv::Mat cupMat = cv::Mat(cup);
                cupMat.convertTo(cupMat, CV_64F);

                cv::Mat tableCoordinatesHomo;
                tableCoordinatesHomo = H * cupMat;
                tableCoordinatesInhomo = {tableCoordinatesHomo.at<double>(1,0)/tableCoordinatesHomo.at<double>(2,0),
                                          tableCoordinatesHomo.at<double>(0,0)/tableCoordinatesHomo.at<double>(2,0)};

                // Display the image with found circles
                for (int i = 0; i < circles.size(); i++) {
                    cv::Vec3i c = circles[i];
                    cv::Point center = cv::Point(c[0], c[1]);
                    //circle center
                    circle(undistortedImg, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
                    //circle outline
                    int radius = c[2];
                    circle(undistortedImg, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
                }

                //cv::imshow("Detected circles", undistortedImg);
                //cv::waitKey(0);
                //std::cout << "Shutting down camera..." << std::endl;
                camera.Close();
                //std::cout << "Camera successfully closed." << std::endl;
                break;
                //}

                ////////////////////////////////////////////////////
                //////////// Here your code ends ///////////////////
                ////////////////////////////////////////////////////

                frame++;


            }
            else
            {
                std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
            }
        }

    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl
                  << e.GetDescription() << std::endl;
        exitCode = 1;
    }

    return tableCoordinatesInhomo;
}
