#include "../include/odometry.hpp"
#include <iostream>

void computeOdometry(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& K) {
    // 1. Detect ORB features and descriptors
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    orb->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

    // 2. Match descriptors using BFMatcher with Hamming distance
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<std::vector<cv::DMatch>> knnMatches;
    matcher.knnMatch(descriptors1, descriptors2, knnMatches, 2);

    // 3. Apply Lowe's ratio test to filter good matches
    std::vector<cv::DMatch> goodMatches;
    const float ratio_thresh = 0.75f;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    // 4. Extract matched keypoints
    std::vector<cv::Point2f> points1, points2;
    for (auto& match : goodMatches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }

    if (points1.size() < 5) {
        std::cerr << "Non abbastanza punti per stimare la posa\n";
        return;
    }

    // 5. Find Essential matrix
    double focal = K.at<double>(0, 0);
    cv::Point2d pp(K.at<double>(0, 2), K.at<double>(1, 2));
    cv::Mat mask;
    cv::Mat E = cv::findEssentialMat(points1, points2, focal, pp, cv::RANSAC, 0.999, 1.0, mask);

    // 6. Recover pose
    cv::Mat R, t;
    int inliers = cv::recoverPose(E, points1, points2, R, t, focal, pp, mask);

    std::cout << "Inliers: " << inliers << std::endl;
    std::cout << "Rotation:\n" << R << std::endl;
    std::cout << "Translation:\n" << t << std::endl;

    // Optional: Draw matches for visualization
    cv::Mat imgMatches;
    cv::drawMatches(img1, keypoints1, img2, keypoints2, goodMatches, imgMatches);
    cv::imshow("Matches", imgMatches);
    cv::waitKey(0);
}