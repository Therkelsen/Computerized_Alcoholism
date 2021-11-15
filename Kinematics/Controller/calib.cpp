#include "calib.h"

Calib::Calib(RobotController &rc, machineVision &mv, std::ostream &ost, std::istream &ist){
    int saveValues = 0;
    while (saveValues != 2) {
        ost << "Pong in place? Enter 1 : ";
        ist >> saveValues;

        if (saveValues == 1) {

            std::vector<double> pongCoords = mv.getObject(1);

            std::array<double, 3> pCoords;

            for (unsigned int i = 0; i < 3; ++i) {
                if (i == 2) {
                    pCoords.at(i) = 0;
                } else {
                    pCoords.at(i) = pongCoords.at(i);
                }
            }

            pWorld.push_back(pCoords);

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
            PRobot.push_back(rc.getTCP());
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
    std::array<double, 3> pPoint{1, 2, 3};
    std::array<double, 3> PPoint{4, 5, 6};

    for (unsigned int i = 0; i < 10; ++i) {
        pWorld.push_back(pPoint);
        PRobot.push_back(PPoint);
    }
}


void Calib::printCoordinates(std::ostream &ost) {
    ost << " __________________________ __________________________ " << "\n";
    ost << "|          pWorld          |          PRobot          |" << "\n";
    ost << " __________________________ __________________________ " << "\n";
    ost << "|px      |py      |pz      |Px      |Py      |Pz      |" << "\n";


    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        if (i > 0) {
           ost << "\n";
        }
        for (unsigned int j = 0; j < 3; ++j) {
            ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << pWorld.at(i).at(j);
        }
        for (unsigned int j = 0; j < 3; ++j) {
            if (j == 2) {
                ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << PRobot.at(i).at(j) << "|";
            } else {
                ost << "|" << std::setw(8) <<  std::left << std::fixed << std::setprecision(2) << PRobot.at(i).at(j);
            }
        }
    }

}

void Calib::calcCentroids() {

    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            centroidW.at(j) += pWorld.at(i).at(j);
            centroidR.at(j) += PRobot.at(i).at(j);
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        centroidW.at(i) /= pWorld.size();
        centroidR.at(i) /= PRobot.size();
    }

}

void Calib::printCentroids(std::ostream &ost) {

    ost << "\n" << "centroidR: ";

    for (unsigned int i = 0; i < 3; ++i) {
        ost << centroidR.at(i) << " ";
    }

    ost << "\n" << "centroidC: ";

    for (unsigned int i = 0; i < 3; ++i) {
        ost << centroidW.at(i) << " ";
    }
}



void Calib::calcQ() {
    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        std::array<double, 3> qPoint, QPoint;

        for (unsigned int j = 0; j < 3; ++j) {
            qPoint.at(j) = pWorld.at(i).at(j) - centroidW.at(j);
            QPoint.at(j) = PRobot.at(i).at(j) - centroidR.at(j);
        }

        qWorld.push_back(qPoint);
        QRobot.push_back(QPoint);
    }

}

void Calib::printQ(std::ostream &ost) {
    ost << "Printing qWorld.." << "\n";

    for (unsigned int i = 0; i < qWorld.size(); ++i) {
        ost << "\n";

        for (unsigned int j = 0; j < 3; ++j) {
            ost << qWorld.at(i).at(j) << " ";
        }
    }

    ost << "Printing QRobot.." << "\n";

    for (unsigned int i = 0; i < qWorld.size(); ++i) {
        ost << "\n";

        for (unsigned int j = 0; j < 3; ++j) {
            ost << QRobot.at(i).at(j) << " ";
        }
    }
}

void Calib::calcH() {
    H = {};

    for (unsigned int i = 0; i < qWorld.size(); ++i) {

        for (unsigned int j = 0; j < 3; ++j) {

            for (unsigned int h = 0; h < 3; ++h) {
                H.at(j).at(h) += QRobot.at(i).at(j) * qWorld.at(i).at(h);
            }
        }
    }
}

void Calib::printH() {

    std::cout << "Printing H:";
    for (unsigned int i = 0; i < 3; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 3; ++j) {
            std::cout << H.at(i).at(j) << " ";
        }
    }


}

void Calib::calcSVD() {
    // H castes til Eigen-matrix
    Eigen::Matrix3d h;

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            h(i,j) = H.at(i).at(j);
        }
    }


    // SVD-objekt af matrix h
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(h, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::Matrix3d u = svd.matrixU();
    Eigen::Matrix3d v = svd.matrixV();

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            U.at(i).at(j) = u(i,j);
            V.at(i).at(j) = v(i,j);
        }
    }

}



void Calib::calcRot() {
    //Transpose matrix U
    std::array<std::array<double, 3>, 3> U_T;

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            U_T.at(i).at(j) = U.at(j).at(i);
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            double temp;
            for (unsigned int h = 0; h < 3; ++h) {
                temp += V.at(i).at(h) * U_T.at(j).at(h);
            }

            R.at(i).at(j) = temp;
        }
    }

}

std::array<std::array<double, 3>, 3> Calib::getRot() {
    return R;
}


void Calib::calcTrans() {
    std::array<double, 3> temp;

    for (unsigned int i = 0; i < 3; ++i) {
        double sum;
        for (unsigned int j = 0; j < 3; ++j) {
            sum += R.at(i).at(j) * centroidR.at(j);
        }
        temp.at(i) = sum;
    }

    for (unsigned int i = 0; i < 3; ++i) {
         T.at(i) = centroidW.at(i) - temp.at(i);
    }

}

std::array<double, 3> Calib::getTrans() {
    return T;
}

void Calib::printCalibration() {

    std::cout << "\n\nRotation matrix of calibration: ";

    for (unsigned int i = 0; i < 3; ++i) {
        std::cout << "\n";
        for (unsigned int j = 0; j < 3; ++j) {
            std::cout << R.at(i).at(j) << " ";
        }
    }

    std::cout << "\n\nTranslational vector of calibration:";
    for (unsigned int i = 0; i < 3; ++i) {
        std::cout << T.at(i) << " ";
    }

}






