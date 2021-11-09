#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include "calib.h"

int main()
{

    Calib calc(std::cout, std::cin);

    calc.printCoordinates(std::cout);

   /*std::vector<std::array<double, 3>> qWorld;

    std::array<double, 3> num1 {{1.25463, 2, 3}};
    std::array<double, 3> num2 {{2, 3, 4}};
    std::array<double, 3> num3 {{5, 6, 7}};

    qWorld.push_back(num1);
    qWorld.push_back(num2);
    qWorld.push_back(num3);



    for (unsigned int i = 0; i < qWorld.size(); ++i) {
        if (i > 0) {
            std::cout << "\n";
        }
        for (unsigned int j = 0; j < 3; ++j) {
            if (j == 2) {
                std::cout << "|" << std::setw(4) << std::left << qWorld.at(i).at(j) << "|";
            } else {
                std::cout << "|" << std::setw(4) << std::left << qWorld.at(i).at(j);
            }

        }
    }

    */

    return 0;
}
