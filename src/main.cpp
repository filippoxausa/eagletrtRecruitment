#include <opencv2/opencv.hpp>
#include "../include/color_detection.hpp"

int main() {
    cv::Mat image = cv::imread("../data/frame_1.png");
    if (image.empty()) {
        std::cerr << "Errore: Impossibile caricare l'immagine.\n";
        return 1;
    }

    // Filtro per ridurre eventuale rumore
    // cv::GaussianBlur(image, blurredImage, cv::Size(3, 3), 0);
    // cv::bilateralFilter(image, filteredImage, 5, 50, 50);

    // Converti in HSV
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    cv::Mat redMask = filterRed(hsvImage);
    cv::Mat blueMask = filterBlue(hsvImage);
    cv::Mat yellowMask = filterYellow(hsvImage);

    cv::imshow("Originale", image);
    cv::imshow("Rossi", redMask);
    cv::imshow("Blu", blueMask);
    cv::imshow("Gialli", yellowMask);

    cv::waitKey(0);
    return 0;
}
