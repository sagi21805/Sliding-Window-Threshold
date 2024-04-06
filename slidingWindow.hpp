#include <iostream>
#include <utility>
#include <vector>
#include <cstdint>
#include <opencv4/opencv2/opencv.hpp>
using std::vector;
using pair = std::pair<uint32_t, uint32_t>;
using cv::Mat;

template<typename T>
struct window {

    T* data;
    uint32_t rows;
    uint32_t cols;
    uint32_t totalElements;

    window(T* data, uint32_t rows, uint32_t cols, uint32_t totalElements) :
        data(data), rows(rows), cols(cols), totalElements(totalElements) {}
};


/**
 * 
 * currently working only for stride = 1 and 2D arrays;
*/
template<typename T>
window<T> slidingWindow(T* arr, pair shape, pair windowSize, uint32_t stride = 1) {

    uint32_t movementRows = ((shape.first - windowSize.first) / stride) + 1;
    uint32_t movementCols = ((shape.second - windowSize.second) / stride) + 1;

    uint32_t numOfWindows = movementRows*movementCols;
    uint32_t numOfOutElements = numOfWindows*windowSize.first*windowSize.second;
    T* outArr = new T[numOfOutElements];
    uint32_t next = 0;
    int32_t offset = 1-windowSize.second;
    for (uint32_t i = 0; i < numOfWindows; i++){
        i % movementCols == 0 ? offset+=windowSize.second-1 : offset+=0;
        for (uint32_t row = 0; row < windowSize.first; row++){
            for (uint32_t col = 0; col < windowSize.second; col++){
                *(outArr+next) = *(arr+col+row*shape.second+i+offset);
                next++;
            }
        }
    }

    return window<T>(outArr, movementRows, movementCols, numOfOutElements);
}

Mat slidingWindowThreshold(Mat img, pair windowSize, uint8_t threshold){
    Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    uchar* imgArr = gray.ptr();
    window window = slidingWindow(imgArr, pair(img.rows, img.cols), windowSize);

    Mat out = Mat::zeros(cv::Size(window.cols, window.rows), CV_8UC1);
    uint32_t numOfWindowElements = windowSize.first*windowSize.second;
    uint32_t sum = 0;

    for (uint32_t row = 0; row < window.rows; row++){
        for (uint32_t col = 0; col < window.cols; col++){
            for (uint32_t element = 0; element < numOfWindowElements; element++){
                sum += *(window.data+element+col*numOfWindowElements+row*window.cols*numOfWindowElements);
            }
            if (sum > threshold*windowSize.first*windowSize.second){
                out.at<uchar>(row, col) = 255;
            }
            sum = 0;
        }
    }
    delete window.data;
    return out;
    //remember to free the ptr at the end
}