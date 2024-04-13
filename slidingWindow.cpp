#include "slidingWindow.hpp"
#include <chrono>
using namespace std::chrono;


int main(){

    cv::Mat liveImg;
    cv::VideoCapture vid("/home/sagi21805/waterlo23.mp4");
    cv::Mat gray;
    while (true){
    if (vid.isOpened()){
            vid.read(liveImg);
            auto start = high_resolution_clock::now();
            gray = slidingWindowThresholdOptimized(liveImg, {2, 2}, 100, 2);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
            std::cout << 1000000000.0 / duration.count() << "\n";

            cv::imshow("2", gray);
            // cv::imshow("3", liveImg);
            cv::waitKey(1);
        }
    }
    return 0;

}   

