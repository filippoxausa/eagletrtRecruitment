#include "../include/odometry.hpp"
#include <iostream>

//// ORB - Oriented FAST and Rotated BRIEF

void computeOdometry(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& K) {
    // Rileva caratteristiche e descrittori ORB
    cv::Ptr<cv::ORB> orb = cv::ORB::create(); // smart pointer
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    // Rileva i keypoints
    orb->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

    // Confronta i descriptor con Brute Force
    // Ogni descrittore viene confrontato con tutti gli altri della seconda immagine
    cv::BFMatcher matcher(cv::NORM_HAMMING); // distanza di Hamming
    // cv::Dmatch rappresenta una corrispondenza tra due descrittori (di due immagini)
    std::vector<std::vector<cv::DMatch>> knnMatches;
    // Per ogni descrittore della prima immagine trova i "2" descrittori più simili
    matcher.knnMatch(descriptors1, descriptors2, knnMatches, 2); 

    // Filtro dei match
    std::vector<cv::DMatch> goodMatches;
    const float ratio_thresh = 0.75f; // per scartare match ambigui o falso positivi
    for (size_t i = 0; i < knnMatches.size(); i++) {
        // Se il primo è molto migliore del secondo match (probabilmente è corretto allora)
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance) { 
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    // Estrae i punti matchati dalle due immagini
    std::vector<cv::Point2f> points1, points2;
    for (auto& match : goodMatches) {
        points1.push_back(keypoints1[match.queryIdx].pt); // indice del keypoint nella prima immagine
        points2.push_back(keypoints2[match.trainIdx].pt); // nella seconda immagine
    }

    if (points1.size() < 5) {
        std::cerr << "Non abbastanza punti per stimare la posizione\n";
        return;
    }

    // Calcola la Essential Matrix
    double focal = K.at<double>(0, 0); // focale (K[0][0])
    cv::Point2d pp(K.at<double>(0, 2), K.at<double>(1, 2)); // punto principale, centro immagine (K[0][2], K[1][2])
    cv::Mat mask;
    cv::Mat E = cv::findEssentialMat(points1, points2, focal, pp, cv::RANSAC, 0.999, 1.0, mask); // RANSAC per escludere gli outliers

    // Stima posizione
    cv::Mat R, t;
    // Match corretti, coerenti col modello dell'Essential Matrix E
    int inliers = cv::recoverPose(E, points1, points2, R, t, focal, pp, mask);

    std::cout << "Inliers: " << inliers << std::endl;
    std::cout << "Rotation:\n" << R << std::endl;
    // t non è assoluta (non si può stimare la scala reale, ho direzione, non metri)
    // verso del vettore spostamento
    std::cout << "Translation:\n" << t << std::endl;

    /*
    I valori (x, y, z) sono nel sistema di coordinate della camera:
    x: orizzontale (destra positiva)
    y: verticale (basso positivo)
    z: avanti (profondità positiva)

    -t
    */

    // Optional: Draw matches for visualization
    cv::Mat imgMatches;
    cv::drawMatches(img1, keypoints1, img2, keypoints2, goodMatches, imgMatches);
    cv::imshow("Matches", imgMatches);
    cv::waitKey(0);
}