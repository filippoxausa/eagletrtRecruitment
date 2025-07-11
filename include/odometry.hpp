#pragma once
#include <opencv2/opencv.hpp>

#define LIMIT_HEIGHT_VEHICLE 330

void computeOdometry(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& K);