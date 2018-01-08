#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

int low_v=0, low_s=0, low_h=0;
int high_v=255, high_s=255, high_h=255;

void on_low_v_thresh_trackbar(int, void *) {
    low_v = std::min(high_v-1, low_v);
    cv::setTrackbarPos("Low V","Object Detection", low_v);
}

void on_high_v_thresh_trackbar(int, void *) {
    high_v = std::max(high_v, low_v+1);
    cv::setTrackbarPos("High V", "Object Detection", high_v);
}

void on_low_s_thresh_trackbar(int, void *) {
    low_s = std::min(high_s-1, low_s);
    cv::setTrackbarPos("Low S","Object Detection", low_s);
}

void on_high_s_thresh_trackbar(int, void *) {
    high_s = std::max(high_s, low_s+1);
    cv::setTrackbarPos("High S", "Object Detection", high_s);
}

void on_low_h_thresh_trackbar(int, void *) {
    low_h= std::min(high_h-1, low_h);
    cv::setTrackbarPos("Low H","Object Detection", low_h);
}

void on_high_h_thresh_trackbar(int, void *) {
    high_h = std::max(high_h, low_h+1);
    cv::setTrackbarPos("High H", "Object Detection", high_h);
}

int main() {
    std::string imageName("im_0000_20180108_000331.jpg");
    cv::Mat frame, threshold;

    frame = cv::imread(imageName, cv::IMREAD_COLOR);
    cv::namedWindow("Video Capture",  cv::WINDOW_NORMAL);
    cv::namedWindow("Object Detection",  cv::WINDOW_NORMAL);

    cv::createTrackbar("Low H","Object Detection", &low_h, 255, on_low_h_thresh_trackbar);
    cv::createTrackbar("High H","Object Detection", &high_h, 255, on_high_h_thresh_trackbar);
    cv::createTrackbar("Low S","Object Detection", &low_s, 255, on_low_s_thresh_trackbar);
    cv::createTrackbar("High S","Object Detection", &high_s, 255, on_high_s_thresh_trackbar);
    cv::createTrackbar("Low V","Object Detection", &low_v, 255, on_low_v_thresh_trackbar);
    cv::createTrackbar("High V","Object Detection", &high_v, 255, on_high_v_thresh_trackbar);

    cv::Mat resizedImage;
    cv::resize(frame, resizedImage, cv::Size(0, 0), 0.5, 0.5);

    cv::Mat hsvImage;
    cv::cvtColor(resizedImage, hsvImage, CV_BGR2HSV);

    while((char) cv::waitKey(1) != 'q'){
        cv::inRange(hsvImage, cv::Scalar(low_h,low_s,low_v), cv::Scalar(high_h,high_s,high_v),threshold);
        cv::imshow("Object Detection",threshold);
    }

    std::cout << "low_h:  " << low_h <<  " low_s: " << low_s <<  " low_v:  " << low_v << std::endl; 
    std::cout << "high_h: " << high_h << " low_s: " << high_s << " high_v: " << high_v << std::endl; 
    return 0;
}

