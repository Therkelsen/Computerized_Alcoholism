#include "calib.h"

Calib::Calib(RobotController &rc, machineVision &mv, std::ostream &ost, std::istream &ist){
    int saveValues = 0;
    while (saveValues != 2) {
        ost << "Pong in place? Enter 1 : ";
        ist >> saveValues;

        if (saveValues == 1) {

            std::vector<double> pongCoords = mv.getBall();

            std::array<double, 3> pCoords;

            for (unsigned int i = 0; i < 3; ++i) {
                if (i == 2) {
                    pCoords.at(i) = 0;
                } else {
                    pCoords.at(i) = pongCoords.at(i);
                }
            }

            pWorldArr.push_back(pCoords);

            saveValues = 0;
            ost << "PONG COORDINATES HAS BEEN COPIED TO VECTOR" << "\n" << "\n";


        } else if (saveValues < 1 || saveValues > 2){
            ost << "Invalid number chosen" << "\n";
            ost << "Ending session";
            saveValues = 2;

        }

        ost << "Robot in place? Enter 1 : ";
        ist >> saveValues;

        if (saveValues == 1) {
            PRobotArr.push_back(rc.getTCP());
            ost << "ROBOT COORDINATES COPIED TO VECTOR \n";
            saveValues = 0;

        } else if (saveValues < 1 || saveValues > 2) {
            ost << "Invalid number chosen" << "\n";
            ost << "Ending session";
            saveValues = 2;
        }

        ost << "\nCopy more points? Enter 1 : \n";
        ost << "Finished? Enter 2 : ";
        ist >> saveValues;

    }
}

//Test-constructor

Calib::Calib() {

    //pWorldArr = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    //PRobotArr = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};

    pWorldArr = {{299, 247.39, 0.00}, {401.03, 449.27, 0.00}, {449.69, 248.15, 0.00}, {499.13, 148.24, 0.00}};
    PRobotArr = {{258.65, -488.52, 210}, {35.59, -474.24, 210}, {199.78, -352.10, 210}, {273.12, -268.25, 210}};
}


void Calib::printCoordinates(std::ostream &ost) {
    ost << " __________________________ __________________________ " << "\n";
    ost << "|          pWorld          |          PRobot          |" << "\n";
    ost << " __________________________ __________________________ " << "\n";
    ost << "|px      |py      |pz      |Px      |Py      |Pz      |" << "\n";


    for (unsigned int i = 0; i < pWorldArr.size(); ++i) {
        if (i > 0) {
           ost << "\n";
        }
        for (unsigned int j = 0; j < 3; ++j) {
            ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << pWorldArr.at(i).at(j);
        }
        for (unsigned int j = 0; j < 3; ++j) {
            if (j == 2) {
                ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << PRobotArr.at(i).at(j) << "|";
            } else {
                ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << PRobotArr.at(i).at(j);
            }
        }
    }

}

void Calib::convertToEigen() {
    pWorld.resize(pWorldArr.size(), 3);
    PRobot.resize(PRobotArr.size(),3);

    for (unsigned int i = 0; i < pWorldArr.size(); ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            pWorld(i,j) = pWorldArr.at(i).at(j);
            PRobot(i,j) = PRobotArr.at(i).at(j);
        }
    }

    std::cout << "\n\nConverted to eigen \n";
    std::cout << pWorld;
    std::cout << "\n\n";
    std::cout << PRobot;
    std::cout << "\n\n";

}

void Calib::calcCentroids() {

    for (unsigned int i  = 0; i < pWorld.rows(); ++i) {
        centroidW += pWorld.row(i);
        centroidR += PRobot.row(i);

    }

    centroidW /= pWorld.rows();
    centroidR /= pWorld.rows();

    std::cout << "\n\nCentroids : \n";
    std::cout << centroidW << "\n\n";
    std::cout << centroidR << "\n\n";

}


void Calib::calcQ() {
    qWorld.resize(pWorldArr.size(), 3);
    QRobot.resize(PRobotArr.size(),3);

    for (unsigned int i = 0; i < pWorld.rows(); ++i) {
        qWorld.row(i) = pWorld.row(i) - centroidW.transpose();
        QRobot.row(i) = PRobot.row(i) - centroidR.transpose();
    }

    std::cout << "\n\nQ : \n";
    std::cout << qWorld << "\n\n";
    std::cout << QRobot << "\n\n";

}


void Calib::calcH() {

    H = Eigen::Matrix3d::Zero();

    for (unsigned int i = 0; i < qWorld.rows(); ++i) {
        H += QRobot.row(i).transpose() * qWorld.row(i);
    }

    std::cout << "\n\nH : \n";
    std::cout << H << "\n\n";

}


void Calib::calcSVD() {
    // SVD-objekt af matrix H
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

    U = svd.matrixU();
    V = svd.matrixV();

    std::cout << "\n\nU : \n";
    std::cout << U;
    std::cout << "\n\nV : \n";
    std::cout << V << "\n\n";

}

void Calib::calcRot() {
    R = V*U.transpose();
}


void Calib::calcTrans() {

    T = centroidW - R*centroidR;
}

void Calib::printCalibration() {

    std::cout << "\n\nRotation matrix from calibration: \n";

    std::cout << R;

    std::cout << "\n\nTranslational vector from calibration: \n";

    std::cout << T;


}
