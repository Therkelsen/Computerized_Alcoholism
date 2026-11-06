# Computerized Alcoholism

[![C++](https://img.shields.io/badge/C%2B%2B-MSVC%2Fgcc-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![OpenCV](https://img.shields.io/badge/OpenCV-5C3EE8?logo=opencv&logoColor=white)](https://opencv.org/)
[![Qt](https://img.shields.io/badge/Qt-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![SQLite](https://img.shields.io/badge/SQLite-07405E?logo=sqlite&logoColor=white)](https://www.sqlite.org/)
[![Universal Robots](https://img.shields.io/badge/Universal_Robots-UR5-006699?logo=robotframework&logoColor=white)](https://www.universal-robots.com/)

## 📄 Academic Project Report

The complete methodology, mathematical modeling, and engineering design for this project are detailed in the university report (in Danish):
[**Gruppe 5 Rapport - Computerized Alcoholism**](https://github.com/Therkelsen/Computerized_Alcoholism/blob/v2/Assets/Gruppe%205%20Rapport.pdf)

## Overview

This repository contains the software stack for an industrial robotics project utilizing a **UR5 series robotic arm** equipped with a Weiss WSG-50 gripper and an industrial camera (Basler pylon) to accurately throw a ping-pong ball into a target cup. 

The software integrates computer vision, coordinate frame transformations, trajectory planning via Jacobian matrix calculations, database management, and real-time robot control via `ur_rtde`.

## System Architecture

* **Machine Vision (`machinevision.cpp`)**: Utilizes Basler pylon and OpenCV to capture images, remove optical lens distortion using intrinsic camera matrices and distortion coefficients, and compute homography perspectives (`cv::getPerspectiveTransform`) to map pixel coordinates to real-world table coordinates. Employs Hough Circle Transforms (`cv::HoughCircles`) to locate the ball and cup dynamically.

* **Robot-to-Table Calibration (`calib.cpp`)**: Implements the Kabsch algorithm using Singular Value Decomposition (SVD) and Eigen matrices to compute precise 3D rotation and translation vectors between the camera/table frame and the robot's TCP (Tool Center Point) frame.

* **Projectile Motion Modeling (`projectilemotion.cpp`)**: Computes the kinematic equations for projectile motion given a target cup position and flight duration. Translates Cartesian velocity vectors into joint velocities (`QDot`) and accelerations using the robot's Jacobian matrix.

* **Robot Control Interface (`robotcontroller.cpp`)**: Built on top of the `ur_rtde` C++ library and `WeissWsg50` gripper driver. Handles precise Cartesian and joint-space movements, vacuum/gripper sequencing, throw initialization, and emergency stopping.

* **Database Engine (`database.cpp`)**: Interfaces with an SQLite local database (`project_db.db`) using Qt SQL drivers to store and retrieve cell parameters, camera intrinsics, distortion coefficients, spatial homography translations/rotations, and experimental throw outcomes to track overall system accuracy.

## Repository Structure

* `Code/main.cpp`: Main entry point handling system initialization, cell selection, state machine sequencing, and the throw execution loop.
* `Code/machinevision.cpp` / `machinevision.h`: Basler camera interfacing, undistortion routines, and circle/object detection for balls and cups.
* `Code/calib.cpp` / `calib.h`: SVD-based spatial calibration routine between robot coordinates and world vision frames.
* `Code/projectilemotion.cpp` / `projectilemotion.h`: Physics modeling for the throw trajectory and Jacobian inverse kinematics mapping.
* `Code/robotcontroller.cpp` / `robotcontroller.h`: UR5 RTDE control wrapper and Weiss gripper orchestration.
* `Code/database.cpp` / `database.h`: SQLite database management layer for configuration persistence and hit statistics.

## Prerequisites & Dependencies

* **Operating System**: Ubuntu 20.04 LTS (or compatible Linux environment for real-time control / URSim simulation)
* **Libraries & Frameworks**:
  * C++11 or higher
  * OpenCV 4.x with contrib modules
  * Qt 5 (with SQLite support)
  * `ur_rtde` (UR Real-Time Data Exchange library)
  * Basler pylon Camera Software Suite
  * Eigen3 math library

## Installation & Setup

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Therkelsen/Computerized_Alcoholism.git
   cd Computerized_Alcoholism
   ```

2. **Install Dependencies (Ubuntu 20.04 reference):**
   * Follow the detailed instructions inside the README installation subsections for setting up **RTDE**, **OpenCV**, and **URSim** (Java 8 + UR Offline Simulator).

3. **Build the Project:**
   * Open the project in Qt Creator or configure via CMake:
     ```bash
     mkdir build && cd build
     cmake ..
     make
     ```

## Usage

1. Start your UR5 robot controller or launch the local **URSim** instance:
   ```bash
   sudo ./start-ursim.sh
   ```
2. Run the compiled application binary:
   ```bash
   ./Computerized_Alcoholism
   ```
3. Follow the console prompt to select your active robot cell (1-4) or simulator (Cell 5). The program will load calibration data, move to the starting position, locate the ball and cup, execute the modeled throwing trajectory, release the ball at the calculated timestamp, and record performance metrics into the SQLite database.