#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

// example: ./ballDetectVideo vi_0001_20180108_023730.mp4 50 165 25 37
int main(int argc, char *argv[]) {
    std::string videoName(argv[1]);
    int min_radius = atoi(argv[2]);
    int max_radius = atoi(argv[3]);
    int param1 = atoi(argv[4]);
    int param2 = atoi(argv[5]);

    cv::VideoCapture cap(videoName);
    cv::VideoWriter video("ballDetect.avi", CV_FOURCC('M','J','P','G'), 20, cv::Size(960, 540));

    if (!cap.isOpened()) {
        std::cout << "Unable to open video: " << videoName << std::endl;
        return -1;
    }
                                  // H   S    V
    cv::Scalar hsv_min = cv::Scalar(143, 80, 109, 0);
    cv::Scalar hsv_max = cv::Scalar(255, 255, 255, 0);

    for (;;) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        cv::Mat resizedImage;
        cv::resize(frame, resizedImage, cv::Size(0, 0), 0.5, 0.5);
        cv::Size s = resizedImage.size();

        cv::Mat hsvImage;
        cv::cvtColor(resizedImage, hsvImage, CV_BGR2HSV);

        cv::Mat thresholded;
        cv::inRange(hsvImage, hsv_min, hsv_max, thresholded);
        cv::GaussianBlur(thresholded, thresholded, cv::Size(9, 9), 0, 0);

        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(thresholded, circles, cv::HOUGH_GRADIENT, 1, s.height/8, param1, param2, min_radius, max_radius);

        for (size_t i = 0; i < circles.size(); i++) {
            cv::Vec3i c = circles[i];
            cv::Point center(c[0], c[1]);
            int radius = c[2];

            cv::circle(resizedImage, center, radius, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
            cv::circle(resizedImage, center, 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
        }

        cv::imshow("ball detect", resizedImage);
        video.write(resizedImage);
        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    cap.release();
    video.release();
    cv::destroyAllWindows();

    return 0;
}
