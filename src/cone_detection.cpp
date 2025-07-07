#include "../include/cone_detection.hpp"

// Restituisce un vettore contenente le coordinate dei centroidi (centro geometrico di un contorno)
std::vector<cv::Point> getConeCenters(const cv::Mat& mask, double areaMin, double areaMax) {
    std::vector<cv::Point> centers;
    std::vector<std::vector<cv::Point>> contours;

    cv::Mat dilated;
	// Espande le aree "bianche"
    cv::dilate(mask, dilated, cv::Mat(), cv::Point(-1, -1), 2);
	cv::imshow("Dilated", dilated);
	cv::waitKey(0);

	// Trova i bordi (chiusi)
    cv::findContours(dilated, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// RETR_EXTERNAL, prende solo i contorni esterni 
	// CHAIN_APPROX_SIMPLE, comprime i vertici significativi

    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area < areaMin || area > areaMax) // scarto gli oggetti troppo piccoli o troppo grandi
            continue;

		// Struttura che contiene informazioni geometriche sul contorno
		// Calcolo il centroide
        cv::Moments M = cv::moments(contour);
        if (M.m00 != 0) { // controllo M.m00 = area non nulla
            int cx = static_cast<int>(M.m10 / M.m00);
            int cy = static_cast<int>(M.m01 / M.m00);
			// Non inserisce i punti oltre l'area di interesse
			if (cy >= LIMIT_HEIGHT_LOW && cy <= LIMIT_HEIGHT_HIGH) centers.emplace_back(cx, cy);
        }
    }

    return centers;
}

void drawCones(cv::Mat& image, const std::vector<cv::Point>& centers, const cv::Scalar& color) {
    for (const auto& pt : centers) {
        cv::circle(image, pt, 4, color, -1);
        // cv::rectangle(image, cv::Point(pt.x - 5, pt.y - 15), cv::Point(pt.x + 5, pt.y + 15), color, 1);
    }
}
