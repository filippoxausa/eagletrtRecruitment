#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

#define LIMIT_HEIGHT_HIGH 365 // Altezza minima in cui rilevare i coni
#define LIMIT_HEIGHT_LOW 210 // Altezza massima in cui rilevare i coni
#define LIMIT_DIST_NORM 40.0 // Distanza massima in cui sovrapporre i coni
#define LIMIT_DIST_X 2.0 // Distanza massima (orizzontale) in cui sovrapporre i coni


std::vector<cv::Point> getConeCenters(const cv::Mat& mask, double areaMin = 25.0, double areaMax = 1000.0);
void drawCones(cv::Mat& image, const std::vector<cv::Point>& centers, const cv::Scalar& color);
