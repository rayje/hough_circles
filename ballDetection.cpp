#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string imageName(argv[1]);

    cv::Mat image = cv::imread(imageName, cv::IMREAD_COLOR);
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(0, 0), 0.5, 0.5);

    cv::Mat hsvImage;
    cv::cvtColor(resizedImage, hsvImage, CV_BGR2HSV);
    cv::imshow("hsvImage", hsvImage);

                                  // H   S    V
    cv::Scalar hsv_min = cv::Scalar(143, 80, 109, 0);
    cv::Scalar hsv_max = cv::Scalar(255, 255, 255, 0);

    cv::Mat thresholded;
    cv::inRange(hsvImage, hsv_min, hsv_max, thresholded);
    cv::imshow("thresholded-inrange", thresholded);

    cv::GaussianBlur(thresholded, thresholded, cv::Size(9, 9), 0, 0);
    cv::imshow("thresholded-blurred", thresholded);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(thresholded, circles, cv::HOUGH_GRADIENT, 1, 10, 100, 30, 70, 300);

    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3i c = circles[i];
        cv::circle(resizedImage, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        cv::circle(resizedImage, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
    }

    cv::imshow("thresholded", resizedImage);

    cv::waitKey(0);
    return 0;
}
