#include <opencv2/opencv.hpp>
#include "../include/color_detection.hpp"

int main() {
    // Carica immagine
    cv::Mat image = cv::imread("../data/frame_1.png");
    if (image.empty()) {
        std::cerr << "Errore: Impossibile caricare l'immagine.\n";
        return 1;
    }

    // Converti in HSV
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    // Ottieni le maschere
    cv::Mat redMask = filterRed(hsvImage);
    cv::Mat blueMask = filterBlue(hsvImage);
    cv::Mat yellowMask = filterYellow(hsvImage);

    // Visualizza
    cv::imshow("Originale", image);
    cv::imshow("Rossi", redMask);
    cv::imshow("Blu", blueMask);
    cv::imshow("Gialli", yellowMask);

    cv::waitKey(0);
    return 0;
}
