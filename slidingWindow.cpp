#include <iostream>
#include <utility>
#include <vector>
#include <cstdint>


using std::vector;
using pair = std::pair<uint32_t, uint32_t>;

/**
 * 
 * currently working only for stride = 1 and 2D arrays;
*/
int32_t* slidingWindow(int32_t* arr, pair shape, pair windowSize, uint32_t stride);

int32_t* slidingWindow(int32_t* arr, pair shape, pair windowSize, uint32_t stride) {

    uint32_t size = shape.first * shape.second;
    uint32_t movementRows = ((shape.first - windowSize.first) / stride) + 1;
    uint32_t movementCols = ((shape.second - windowSize.second) / stride) + 1;
    uint32_t numOfWindows = movementRows*movementCols;
    uint32_t numOfOutElements = numOfWindows*windowSize.first*windowSize.second;
    int32_t* outArr = new int32_t[numOfOutElements];
    uint32_t next = 0;
    int32_t offset = -1;
    for (uint32_t i = 0; i < numOfWindows; i++){
        if (i % movementCols == 0){ offset++; }
        for (uint32_t row = 0; row < windowSize.first; row++){
            for (uint32_t col = 0; col < windowSize.second; col++){
                *(outArr+next) = *(arr+col+row*shape.second+i+offset);
                next++;
            }
        }
    }

    return outArr;
}

int main(){

    uint32_t size = 20;

    int32_t arr[size] = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11,12,13,14,15,
        16, 17, 18, 19, 20
    };

    pair shape = {4, 5}; // rows, cols
    pair windowSize = {2, 2}; // row, col

    int32_t* windows = slidingWindow(arr, shape, windowSize, 1);
    for (uint32_t i = 0; i < 12; i++){

        std::cout << "[";  
        for (uint32_t j = 0; j < 4; j++){
            std::cout << *(windows+j+4*i) << ", ";
        }
        std::cout << "]\n";
    }

    return 0;

}