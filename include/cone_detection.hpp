#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

#define LIMIT_HEIGHT_HIGH 365
#define LIMIT_HEIGHT_LOW 210

std::vector<cv::Point> getConeCenters(const cv::Mat& mask, double areaMin = 25.0, double areaMax = 1000.0);
void drawCones(cv::Mat& image, const std::vector<cv::Point>& centers, const cv::Scalar& color);
