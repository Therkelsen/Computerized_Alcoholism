#include "calib.h"

Calib::Calib(std::ostream &ost, std::istream &ist){
    int saveValues = 0;
    while (saveValues != 2) {
        ost << "Place robotic arm at pong ball" << std::endl;

        ost << "Robot in place? Enter 1 : " << "\n";
        ost << "Finished noting points? Enter 2 : ";
        ist >> saveValues;

        if (saveValues == 1) {

            //Kalder metode på rc-objekt som returnerer TCP pose af robot
            //Kalder metode på mv-objekt som returnerer boldsens koordinater
            //Gemmer disse værdier i member vectors

            saveValues = 0;
            ost << "COORDINATES HAS BEEN COPIED TO VECTORS" << "\n" << "\n";


        } else if (saveValues < 1 || saveValues > 2){
            ost << "Invalid number chosen" << "\n" << std::endl;

        }
    }

}

void Calib::printCoordinates(std::ostream &ost) {
    ost << " _______________________ _______________________ " << "\n";
    ost << "|         pWorld        |        PRobot         |" << "\n";
    ost << " _______________________ _______________________ " << "\n";
    ost << "|px     |py     |pz     |Px     |Py     |Pz     |" << "\n";


    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        if (i > 0) {
           ost << "\n";
        }
        for (unsigned int j = 0; j < 3; ++j) {
            ost << "|" << std::setw(8) <<  std::left << pWorld.at(i).at(j);
        }
        for (unsigned int j = 0; j < 3; ++j) {
            if (j == 2) {
                ost << "|" << std::setw(8) <<  std::left << PRobot.at(i).at(j) << "|";
            } else {
                ost << "|" << std::setw(8) <<  std::left << PRobot.at(i).at(j);
            }
        }
    }

}

void Calib::calcCentroids() {

    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            centroidW[j] += pWorld.at(i).at(j);
            centroidR[j] += PRobot.at(i).at(j);
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        centroidW[i] /= 4;
        centroidR[i] /= 4;
    }

}

void Calib::calcQ() {
    for (unsigned int i = 0; i < pWorld.size(); ++i) {
        std::array<double, 3> qPoint, QPoint;

        for (unsigned int j = 0; j < 3; ++j) {
            qPoint.at(j) = pWorld.at(i).at(j) - centroidW[j];
            QPoint.at(j) = PRobot.at(i).at(j) - centroidR[j];
        }

        qWorld.push_back(qPoint);
        QRobot.push_back(QPoint);
    }

}

void Calib::calcH() {
    for (unsigned int i = 0; i < qWorld.size(); ++i) {
        std::array<std::array<double, 3>, 3> temp;

        for (unsigned int j = 0; j < 3; ++j) {
            for (unsigned int h = 0; h < 3; ++h) {
                temp.at(j).at(h) = QRobot.at(i).at(j) * qWorld.at(i).at(h);
            }
        }

        for (unsigned int j = 0; j < 3; ++j) {
            for (unsigned int h = 0; h < 3; ++h) {
                H.at(j).at(h) += temp.at(j).at(h);
            }
        }

    }

}

void Calib::calcSVD() {

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

void Calib::calcTrans() {
    std::array<double, 3> temp;

    for (unsigned int i = 0; i < 3; ++i) {
        double sum;
        for (unsigned int j = 0; j < 3; ++j) {
            sum += R.at(i).at(j) * centroidR[j];
        }
        temp.at(i) = sum;
    }

    for (unsigned int i = 0; i < 3; ++i) {
        T.at(i) = centroidW[i] - temp.at(i);
    }


}



