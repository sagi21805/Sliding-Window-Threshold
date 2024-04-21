#include "slidingWindow.hpp"

Mat slidingWindowThresholdOptimized(Mat img, pair windowSize, uint8_t threshold){
    
    Mat out;
    const uint32_t movementRows = (img.rows - windowSize.first) + 1;
    const uint32_t movementCols = (img.cols - windowSize.second)+ 1;
    const uint32_t thresh = threshold*windowSize.first*windowSize.second;
    out = Mat::zeros(cv::Size(movementCols, movementRows), CV_8UC1);
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    uchar* arr = img.ptr();
    uint32_t sum = 0;
    int32_t offset = 1-windowSize.second;
    for (uint32_t imgRow = 0; imgRow < movementRows; imgRow++){
        offset += windowSize.second-1;
        for (uint32_t imgCol = 0; imgCol < movementCols; imgCol++){
            for (uint32_t windowRow = 0; windowRow < windowSize.first; windowRow++){
                for (uint32_t windowCol = 0; windowCol < windowSize.second; windowCol++){
                    sum += *(arr + windowCol + windowRow*img.cols + imgCol + imgRow*movementCols + offset);
                }
            }
            if (sum > thresh){
                out.at<uchar>(imgRow, imgCol) = 255;
            }
            sum = 0;
        }
    }
    return out;
}

void slidingWindowOptimized(Mat img, pair windowSize) {        
    const uint32_t movementRows = (img.rows - windowSize.first) + 1;
    const uint32_t movementCols = (img.cols - windowSize.second) + 1;
    // cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    uchar* arr = img.ptr();
    int32_t offset = 1-windowSize.second;
    for (uint32_t imgRow = 0; imgRow < movementRows; imgRow++){
        offset += windowSize.second-1;
        for (uint32_t imgCol = 0; imgCol < movementCols; imgCol++){
            std::cout << "\n";
            for (uint32_t windowRow = 0; windowRow < windowSize.first; windowRow++){
                std::cout << "\n";
                for (uint32_t windowCol = 0; windowCol < windowSize.second; windowCol++){
                    std::cout << (int) *(arr + windowCol + windowRow*img.cols + imgCol + imgRow*movementCols + offset)
                    << " ";
                }
            }
        }
    }
}