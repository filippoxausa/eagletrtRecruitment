#ifndef COLOR_FILTER_HPP
#define COLOR_FILTER_HPP

#include <opencv2/opencv.hpp>

void createColorTrackbars(const std::string& windowName);
cv::Mat applyHSVFilter(const cv::Mat& hsv, const std::string& prefix);

#endif
