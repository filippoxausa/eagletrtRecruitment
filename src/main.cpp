#include <opencv2/opencv.hpp>
#include "color_filter.hpp"

int main() {
    cv::Mat img = cv::imread("../data/frame_1.png");
    if (img.empty()) {
        std::cerr << "Errore nel caricamento dell'immagine\n";
        return -1;
    }

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // Crea le trackbar per il filtro dinamico interattivo
    createColorTrackbars("Dynamic Mask");

    while (true) {
        cv::Mat redMask = applyHSVFilter(hsv, "Dynamic Mask");

        cv::imshow("Originale", img);
        cv::imshow("Dynamic Mask", redMask);

        // Esci con 'ESC'
        char key = (char) cv::waitKey(30);
        if (key == 27) break;
    }

    return 0;
}
