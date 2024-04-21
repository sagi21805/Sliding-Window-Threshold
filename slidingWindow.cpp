#include "slidingWindow.hpp"

bool strideIsValid(Mat img, pair windowSize, uint32_t stride){
    return (windowSize.first >= stride && windowSize.second >= stride 
            && !((img.rows - windowSize.first) % stride) && !((img.cols - windowSize.second) % stride));
}

Mat slidingWindowThresholdOptimized(Mat img, pair windowSize, uint8_t threshold, uint32_t stride){
    
    Mat out;
    if (strideIsValid(img, windowSize, stride)) {
        const uint32_t movementRows = ((img.rows - windowSize.first)  / stride) + 1;
        const uint32_t movementCols = ((img.cols - windowSize.second) / stride) + 1;
        const uint32_t thresh = threshold*windowSize.first*windowSize.second;
        out = Mat::zeros(cv::Size(movementCols, movementRows), CV_8UC1);
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        uchar* arr = img.ptr();
        uint32_t sum = 0;
        int32_t offset = stride-windowSize.second;
        for (uint32_t imgRow = 0; imgRow < movementRows; imgRow++){
            offset += windowSize.second-stride;
            for (uint32_t imgCol = 0; imgCol < movementCols; imgCol++){
                for (uint32_t windowRow = 0; windowRow < windowSize.first; windowRow++){
                    for (uint32_t windowCol = 0; windowCol < windowSize.second; windowCol++){
                        sum += *(arr + windowCol + windowRow*img.cols + imgCol*stride + imgRow*movementCols*stride*stride + offset);
                    }
                }
                if (sum > thresh){
                    out.at<uchar>(imgRow, imgCol) = 255;
                }
                sum = 0;
            }
        }
    }
    else {
        throw std::runtime_error("stride is not valid");
    }

    return out;
}

void slidingWindowOptimized(Mat img, pair windowSize, uint32_t stride) {        
    if (strideIsValid(img, windowSize, stride)) {
        const uint32_t movementRows = ((img.rows - windowSize.first)  / stride) + 1;
        const uint32_t movementCols = ((img.cols - windowSize.second) / stride) + 1;
        // cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        uchar* arr = img.ptr();
        for (uint i = 0; i < 24; i++) {
            std::cout << (int) arr[i] << " ";
        }
        int32_t offset = stride-windowSize.second;
        for (uint32_t imgRow = 0; imgRow < movementRows; imgRow++){
            offset += windowSize.second-stride;
            for (uint32_t imgCol = 0; imgCol < movementCols; imgCol++){
                std::cout << "\n";
                for (uint32_t windowRow = 0; windowRow < windowSize.first; windowRow++){
                    std::cout << "\n";
                    for (uint32_t windowCol = 0; windowCol < windowSize.second; windowCol++){
                        std::cout << (int) *(arr + windowCol + windowRow*img.cols + imgCol*stride + imgRow*movementCols*stride*stride + offset)
                        << " ";
                    }
                }
            }
        }
    }

    else {
        throw std::runtime_error("stride is not valid");
    }
}