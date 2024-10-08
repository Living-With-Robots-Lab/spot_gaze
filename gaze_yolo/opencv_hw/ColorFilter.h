#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat _bSub, _bThresh, _bContourMask, _blueCupImg;
    cv::Mat _gSub, _gThresh, _gContourMask, _greenCupImg;
    cv::Mat _rSub, _rThresh, _rContourMask, _redCupImg;
    cv::Mat _bgrMask, _bgrCupImg;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();
};

#endif