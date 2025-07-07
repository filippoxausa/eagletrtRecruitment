#pragma once
#include <opencv2/opencv.hpp>

cv::Mat filterRed(const cv::Mat& hsv);
cv::Mat filterBlue(const cv::Mat& hsv);
cv::Mat filterYellow(const cv::Mat& hsv);
