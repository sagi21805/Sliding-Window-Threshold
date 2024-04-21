#include <iostream>
#include <utility>
#include <vector>
#include <cstdint>
#include <opencv4/opencv2/opencv.hpp>
#include <stdexcept>  

using std::vector;
using pair = std::pair<uint32_t, uint32_t>;
using cv::Mat;

bool strideIsValid(Mat img, pair size, uint32_t stride);

Mat slidingWindowThresholdOptimized(Mat img, pair windowSize, uint8_t threshold, uint32_t stride);

void slidingWindowOptimized(Mat img, pair windowSize, uint32_t stride);