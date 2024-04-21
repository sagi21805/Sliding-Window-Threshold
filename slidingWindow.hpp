#include <iostream>
#include <utility>
#include <vector>
#include <cstdint>
#include <opencv4/opencv2/opencv.hpp>
#include <stdexcept>  

using std::vector;
using pair = std::pair<uint32_t, uint32_t>;
using cv::Mat;


Mat slidingWindowThresholdOptimized(Mat img, pair windowSize, uint8_t threshold);

void slidingWindowOptimized(Mat img, pair windowSize);