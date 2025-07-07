#include "../include/color_detection.hpp"

cv::Mat filterRed(const cv::Mat& hsv) {
    cv::Mat mask1, mask2, redMask;
    // ROSSO ha due range nell'HSV
	// angolo del cerchio dei colori (0-179)
    cv::inRange(hsv, cv::Scalar(0, 160, 160), cv::Scalar(10, 255, 255), mask1);
    cv::inRange(hsv, cv::Scalar(160, 160, 160), cv::Scalar(179, 255, 255), mask2);
    cv::bitwise_or(mask1, mask2, redMask);
    return redMask;
}

cv::Mat filterBlue(const cv::Mat& hsv) {
    cv::Mat blueMask;
    cv::inRange(hsv, cv::Scalar(99, 60, 105), cv::Scalar(115, 255, 255), blueMask);
    return blueMask;
}

cv::Mat filterYellow(const cv::Mat& hsv) {
    cv::Mat yellowMask;
    cv::inRange(hsv, cv::Scalar(10, 82, 200), cv::Scalar(20, 255, 255), yellowMask);
    return yellowMask;
}