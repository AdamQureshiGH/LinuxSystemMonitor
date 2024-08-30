/*#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "system.h"
#include "process.h"
#include <unistd.h>
#include "format.h"
#include <iomanip>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : procID(pid) {  }
// TODO: Return this process's ID
int Process::Pid() const { 
    return procID;
 }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
   
std::string uidStr = std::to_string(procID);
    long uptime = std::stoul(System::readFile("/proc/uptime", 1, false, true));
    long ticks_per_second = sysconf(_SC_CLK_TCK);

    unsigned long long int utime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 14, false, true));
    unsigned long long int stime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 15, false, true));
    unsigned long long int cutime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 16, false, true));
    unsigned long long int cstime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 17, false, true));
    unsigned long long int starttime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 22, false, true));

    unsigned long long int total_time = utime + stime + cutime + cstime;

    float seconds = static_cast<float>(uptime) - (static_cast<float>(starttime) / ticks_per_second);

    float cpu_usage = ((total_time / ticks_per_second) / seconds) / 10.0f;

    return cpu_usage;
 }

// TODO: Return the command that generated this process
string Process::Command() { 

        std::string uidStr = std::to_string(procID);
    std::string cmd = System::readFile("/proc/" + uidStr + "/cmdline",1,true,false);
    return cmd;
 }

// TODO: Return this process's memory utilization
string Process::Ram() { 
        std::string uidStr = std::to_string(procID);

    float ramMb = System::FindValueViaKey<float>("/proc/" + uidStr + "/status","VmSize:")/1000;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << ramMb;
    return stream.str();
 }

// TODO: Return the user (name) that generated this process
string Process::User() { 
std::string pidStr = std::to_string(procID);

    std::string uid = System::FindValueViaKey<string>("/proc/" + pidStr + "/status", "Uid:");
        //std::cout << "Process ID: " << procID << " has UID: " << uid << " and maps to username: " << System::FindValueViaKey<string>("/proc/" + uidStr + "/status", "Uid:"); << std::endl;

    return System::findUsernameByUID("/etc/passwd", std::stoi(uid));
 }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 

    std::string uidStr = std::to_string(procID);
    
    
    std::string str = System::readFile("/proc/" + uidStr + "/stat", 22, false, true);
    long int startTime = std::stol(str);
    
 
    long int clockTicksPerSec = sysconf(_SC_CLK_TCK);
    
    
    long int startTimeInSeconds = startTime / clockTicksPerSec;
    
   
    std::string uptimeStr = System::readFile("/proc/uptime", 1, false, true);
    long int systemUptime = std::stol(uptimeStr.substr(0, uptimeStr.find(" "))); // Extract the first number
    
    long seconds = systemUptime - startTimeInSeconds;
    
    return seconds;
 }
  
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {return this->CpuUtilization() > a.CpuUtilization(); }*/
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "system.h"
#include "process.h"
#include <unistd.h>
#include "format.h"
#include <iomanip>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : procID(pid) {  }

int Process::Pid() const { 
    return procID;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    std::string uidStr = std::to_string(procID);
    long uptime = std::stoul(System::readFile("/proc/uptime", 1, false, true));
    long ticks_per_second = sysconf(_SC_CLK_TCK);

    unsigned long long int utime = 0;
    unsigned long long int stime = 0;
    unsigned long long int cutime = 0;
    unsigned long long int cstime = 0;
    unsigned long long int starttime = 0;

    if (System::isStringValidForStoll(System::readFile("/proc/" + uidStr + "/stat", 14, false, true))) {
        utime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 14, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/" + uidStr + "/stat", 15, false, true))) {
        stime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 15, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/" + uidStr + "/stat", 16, false, true))) {
        cutime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 16, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/" + uidStr + "/stat", 17, false, true))) {
        cstime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 17, false, true));
    }
    if (System::isStringValidForStoll(System::readFile("/proc/" + uidStr + "/stat", 22, false, true))) {
        starttime = std::stoll(System::readFile("/proc/" + uidStr + "/stat", 22, false, true));
    }

    unsigned long long int total_time = utime + stime + cutime + cstime;
    float seconds = static_cast<float>(uptime) - (static_cast<float>(starttime) / ticks_per_second);
    float cpu_usage = ((total_time / ticks_per_second) / seconds) / 10.0f;

    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    std::string uidStr = std::to_string(procID);
    return System::readFile("/proc/" + uidStr + "/cmdline", 1, true, false);
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    std::string uidStr = std::to_string(procID);
    float ramMb = System::FindValueViaKey<float>("/proc/" + uidStr + "/status", "VmSize:") / 1000;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << ramMb;
    return stream.str();
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    std::string pidStr = std::to_string(procID);
    std::string uid = System::FindValueViaKey<string>("/proc/" + pidStr + "/status", "Uid:");
    return System::findUsernameByUID("/etc/passwd", std::stoi(uid));
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    std::string uidStr = std::to_string(procID);
    std::string str = System::readFile("/proc/" + uidStr + "/stat", 22, false, true);
    long int startTime = std::stol(str);
    long int clockTicksPerSec = sysconf(_SC_CLK_TCK);
    long int startTimeInSeconds = startTime / clockTicksPerSec;
    std::string uptimeStr = System::readFile("/proc/uptime", 1, false, true);
    long int systemUptime = std::stol(uptimeStr.substr(0, uptimeStr.find(" ")));
    long seconds = systemUptime - startTimeInSeconds;
    return seconds;
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return this->CpuUtilization() > a.CpuUtilization();
}