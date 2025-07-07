#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::imread("../data/frame_1.png");

    if (image.empty()) {
        std::cerr << "Errore: Impossibile caricare l'immagine" << std::endl;
        return 1;
    }

    cv::imshow("Percorso", image);
    cv::waitKey(0);  
    return 0;
}
