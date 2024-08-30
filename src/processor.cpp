/*#include "processor.h"
#include "system.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  
   unsigned long long int user = std::stoll(System::readFile("/proc/stat", 2, false, true));
    unsigned long long int nice = std::stoll(System::readFile("/proc/stat", 3, false, true));
    unsigned long long int system = std::stoll(System::readFile("/proc/stat", 4, false, true));
    unsigned long long int idle = std::stoll(System::readFile("/proc/stat", 5, false, true));
    unsigned long long int iowait = std::stoll(System::readFile("/proc/stat", 6, false, true));
    unsigned long long int irq = std::stoll(System::readFile("/proc/stat", 7, false, true));
    unsigned long long int softirq = std::stoll(System::readFile("/proc/stat", 8, false, true));
    unsigned long long int steal = std::stoll(System::readFile("/proc/stat", 9, false, true));

    unsigned long long int idle_time = idle + iowait;
    unsigned long long int non_idle = user + nice + system + irq + softirq + steal;
    unsigned long long int total = idle_time + non_idle;

    return static_cast<float>(non_idle) / static_cast<float>(total);
}
*/
#include "processor.h"
#include "system.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    unsigned long long int user = 0;
    unsigned long long int nice = 0;
    unsigned long long int system = 0;
    unsigned long long int idle = 0;
    unsigned long long int iowait = 0;
    unsigned long long int irq = 0;
    unsigned long long int softirq = 0;
    unsigned long long int steal = 0;

    if (System::isStringValidForStoll(System::readFile("/proc/stat", 2, false, true))) {
        user = std::stoll(System::readFile("/proc/stat", 2, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 3, false, true))) {
        nice = std::stoll(System::readFile("/proc/stat", 3, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 4, false, true))) {
        system = std::stoll(System::readFile("/proc/stat", 4, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 5, false, true))) {
        idle = std::stoll(System::readFile("/proc/stat", 5, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 6, false, true))) {
        iowait = std::stoll(System::readFile("/proc/stat", 6, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 7, false, true))) {
        irq = std::stoll(System::readFile("/proc/stat", 7, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 8, false, true))) {
        softirq = std::stoll(System::readFile("/proc/stat", 8, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/stat", 9, false, true))) {
        steal = std::stoll(System::readFile("/proc/stat", 9, false, true));
    }

    unsigned long long int idle_time = idle + iowait;
    unsigned long long int non_idle = user + nice + system + irq + softirq + steal;
    unsigned long long int total = idle_time + non_idle;

    return static_cast<float>(non_idle) / static_cast<float>(total);
}