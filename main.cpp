#include "slidingWindow.hpp"
#include <chrono>
using namespace std::chrono;

void test() {

    uchar testArray[] {
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
     10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
     20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
     30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
     40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
     50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
     60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 
     70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
     80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 
     90, 91, 92, 93, 94, 95, 96, 97, 98, 99
    };

    cv::Mat A(10,10,CV_8U);
    std::memcpy(A.data, testArray, 10*10*sizeof(uchar));

    slidingWindowOptimized(A, {4, 4}, 2);

}


int main(){

    test();
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

