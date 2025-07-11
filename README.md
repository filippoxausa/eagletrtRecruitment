# eagletrtRecruitment
Perception project for my recruitment at E-Agle Team of University of Trento

# 🏎️ Driverless - Perception Module (Image Path)

This project implements a **perception module** following the **image-based pipeline**.  
The goal is to process a sequence of camera frames to:
- detect and classify traffic cones (blue, yellow, red),
- extract the track boundaries,
- estimate the vehicle’s motion (odometry) between frames.

---

## 📁 Project Structure

```text
eagletrtRecruitment/
├── build/ # Build directory
├── data/ # Input images (e.g., frame_1.png, frame_2.png)
├── include/ # Header files
│ └── color_detection.hpp
│ └── cone_detection.hpp
│ └── odometry.hpp
├── src/ # Source code
│ └── main.cpp # Main program
│ └── color_detection.cpp # Detect objects by color
│ └── cone_detection.cpp # Detect cones and path
│ └── odometry.cpp # Odometry between frames
├── CMakeLists.txt # CMake configuration
├── README.md # Project description
└── ...
```

---

## ✅ Requirements

Make sure the following tools are installed:

- [OpenCV](https://opencv.org/) ≥ 4.x
- [CMake](https://cmake.org/) ≥ 3.10
- [g++](https://gcc.gnu.org/) with C++17 support
- Tested OS: **Ubuntu 24.04**

To install the required packages on Ubuntu:

```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev
```

---

## ⚙️ Build and Run

1. Clone the repository:
```bash
git clone https://github.com/filippoxausa/eagletrtRecruitment.git
cd eagletrtRecruitment
```

2. Create the build directory and generate the Makefile:
```bash
mkdir build
cd build
cmake ..
```

3. Compile the project:
```bash
make
```

4. Run the executable:
```bash
./main
```

---

## 🖼️ Input Data

The input images used for detection and odometry are stored in the data/ folder.
- frame_1.png: first frame of the scene
- frame_2.png: second frame for odometry estimation

Make sure these files are present before running the program.

---


## 🔍 Implemented Features

- Cone detection using HSV color thresholding
- Cone classification by color: blue (left), yellow (right), red (start)
- Track edge extraction by connecting detected cones
- Monocular visual odometry using ORB, RANSAC, and recoverPose
