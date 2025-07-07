#include "../include/color_filter.hpp"

void createColorTrackbars(const std::string& windowName) {
    cv::namedWindow(windowName);

    cv::createTrackbar("H_MIN", windowName, nullptr, 179);
    cv::createTrackbar("H_MAX", windowName, nullptr, 179);
    cv::createTrackbar("S_MIN", windowName, nullptr, 255);
    cv::createTrackbar("S_MAX", windowName, nullptr, 255);
    cv::createTrackbar("V_MIN", windowName, nullptr, 255);
    cv::createTrackbar("V_MAX", windowName, nullptr, 255);

    cv::setTrackbarPos("H_MIN", windowName, 0);
    cv::setTrackbarPos("H_MAX", windowName, 10);
    cv::setTrackbarPos("S_MIN", windowName, 100);
    cv::setTrackbarPos("S_MAX", windowName, 255);
    cv::setTrackbarPos("V_MIN", windowName, 100);
    cv::setTrackbarPos("V_MAX", windowName, 255);
}

cv::Mat applyHSVFilter(const cv::Mat& hsv, const std::string& windowName) {
    int h_min = cv::getTrackbarPos("H_MIN", windowName);
    int h_max = cv::getTrackbarPos("H_MAX", windowName);
    int s_min = cv::getTrackbarPos("S_MIN", windowName);
    int s_max = cv::getTrackbarPos("S_MAX", windowName);
    int v_min = cv::getTrackbarPos("V_MIN", windowName);
    int v_max = cv::getTrackbarPos("V_MAX", windowName);

    cv::Mat mask;
    cv::inRange(hsv,
                cv::Scalar(h_min, s_min, v_min),
                cv::Scalar(h_max, s_max, v_max),
                mask);
    return mask;
}
