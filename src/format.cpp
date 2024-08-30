#include <string>
#include <cmath>
#include "format.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long totalSeconds) {
    

    long hours = totalSeconds / 3600;           
    long minutes = (totalSeconds % 3600) / 60;   
    long seconds = totalSeconds % 60;            

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;

    return oss.str();

     }