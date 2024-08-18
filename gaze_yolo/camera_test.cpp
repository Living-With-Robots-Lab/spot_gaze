//code from https://stackoverflow.com/questions/61454838/ubuntu-19-10-enabling-and-using-raspberry-pi-camera-module-v2-1

#include <opencv2/highgui.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/videoio.hpp>
using namespace cv;
int main(int argc, char** argv){

    VideoCapture cap;
    cap.open(0);
    Mat frame;
    for(;;){
        cap.read(frame);
        if (frame.empty()){
            std::cerr << "Error";}
        imshow("Live", frame);
    }
    return 0;
    }