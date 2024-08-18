#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    imshow("color", _bgrCupImg);
    waitKey(50);
}

void ColorFilter::findBlue() {
    cv::subtract(_chans[0], _chans[2], _bSub);
    cv::threshold(_bSub, _bThresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(_bThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    _bContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( _bContourMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );

    _blueCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(_blueCupImg, _bContourMask);

}

void ColorFilter::findGreen() {
    cv::subtract(_chans[1], _chans[0], _gSub);
    cv::threshold(_gSub, _gThresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(_gThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    _gContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( _gContourMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );

    _greenCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(_greenCupImg, _gContourMask);

}

void ColorFilter::findRed() {
    cv::subtract(_chans[2], _chans[1], _rSub);
    cv::threshold(_rSub, _rThresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(_rThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    _rContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( _rContourMask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );

    _redCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_redCupImg, _rContourMask);

}

void ColorFilter::findBGR() {
    _bgrMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _bgrCupImg = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    cv::bitwise_or(_bContourMask, _gContourMask, _bgrMask);
    cv::bitwise_or(_bgrMask, _rContourMask, _bgrMask);
    _frame.copyTo(_bgrCupImg, _bgrMask);
}