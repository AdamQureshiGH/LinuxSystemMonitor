#include <unistd.h>
/*#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include <iostream>
#include <sstream>
#include "linux_parser.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
  cpu_.User(std::stoll(System::readFile("/proc/stat", 2, false, true)));
    cpu_.Nice(std::stoll(System::readFile("/proc/stat", 3, false, true)));
    cpu_.System(std::stoll(System::readFile("/proc/stat", 4, false, true)));
    cpu_.Idle(std::stoll(System::readFile("/proc/stat", 5, false, true)));
    cpu_.IOwait(std::stoll(System::readFile("/proc/stat", 6, false, true)));
    cpu_.IRQ(std::stoll(System::readFile("/proc/stat", 7, false, true)));
    cpu_.SoftIRQ(std::stoll(System::readFile("/proc/stat", 8, false, true)));
    cpu_.Steal(std::stoll(System::readFile("/proc/stat", 9, false, true)));

    // Calculate the total time and update it
    cpu_.TotalTime(cpu_.User() + cpu_.Nice() + cpu_.System() + cpu_.Idle() + cpu_.IOwait() + cpu_.IRQ() + cpu_.SoftIRQ() + cpu_.Steal());

    return cpu_;
 }
std::string System::findUsernameByUID(const std::string &filePath, int uid) {
    std::ifstream passwdFile(filePath);
    std::string line;
    
    if (!passwdFile.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return "";
    }
    
    while (std::getline(passwdFile, line)) {
        std::stringstream ss(line);
        std::string username, x, uidStr;
        int fileUID;
        
        std::getline(ss, username, ':');
        
        // Skip the x field
        std::getline(ss, x, ':');
        
        std::getline(ss, uidStr, ':');
        fileUID = std::stoi(uidStr);
        
        if (fileUID == uid) {
            passwdFile.close();
            return username;
        }
    }
    
    passwdFile.close();
    return ""; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{
    
      vector<int> pids = LinuxParser::Pids();

    // Clear the current processes vector
    procsVec.clear();

    // Populate the processes vector with new Process objects
    for (int pid : pids) {
        procsVec.emplace_back(Process(pid)); // Use emplace_back to construct in place
    }

    // Sort the processes vector (optional, based on your requirement)
    std::sort(procsVec.begin(), procsVec.end());

    return procsVec;
}

 std::string System::readFile(std::string fileName, int lineNum, bool getLine, bool extractionOperator)
{
    std::string identifier{};
    std::fstream in_file{fileName, std::ios::in};
    if(in_file.is_open())
    {    
        if(getLine == true)
        {
            for(int i = 0; i < lineNum; i++)
            {
                std::getline(in_file,identifier);
            }
        }
        else if (extractionOperator == true)
        {
            for(int i = 0; i < lineNum; i++)
            {
                in_file >> identifier;
            }
        }
        
    }
    else{
        std::cout << "Im trying to open" << fileName << std::endl;
        std::cout << "File isnt opening" << std::endl;
        return "";
    }
    in_file.close();
    
    return identifier; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return readFile("/proc/version", 3, false, true);
 }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    std::string memTotal = readFile("/proc/meminfo",2,false,true);
    float memTotalF = std::stof(memTotal);
    std::string memFree = readFile("/proc/meminfo",5,false,true);
    float memFreeF = std::stof(memFree);
    //Go from KB to GB

    memTotalF = memTotalF / 1000000.0f;
    memFreeF = memFreeF / 1000000.0f;
    float usedMemory = memTotalF - memFreeF;
    return (usedMemory/memTotalF) / 10.0f; 
    }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return readFile("/etc/os-release", 5, true, false);
    }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() 
{
     std::ifstream file("/proc/stat");
    //string of numbers
    std::string line;
    //what we return
    int processes = 0;

    while (std::getline(file, line)) {
        //the capabilities of a stream but for a string
        std::istringstream linestream(line);
        std::string key;
        int value;

        linestream >> key;

        if (key == "procs_running") {
            linestream >> value;
            processes = value;
            break;  // No need to continue reading once we've found the value
        }}
        return processes;
}


// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int opt = FindValueViaKey<int>("/proc/stat","processes");
    return opt;
  
 }
 

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {  
    std::ifstream file("/proc/uptime");
    std::string line;
    
    if (file.is_open()) {
        std::getline(file, line);
        std::istringstream linestream(line);

        double uptime;
        linestream >> uptime;  // Read the first number as a double

        file.close();

        // Convert uptime to long int (seconds)
        return static_cast<long int>(uptime);
    }

    std::cerr << "Error: Could not open /proc/uptime" << std::endl;
    return 0;  // Return 0 if the file cannot be opened
    
 }
*/
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;

// Helper function to check if a string is a valid number for stoll conversion
bool System::isStringValidForStoll(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

// Helper function to check if a file exists
bool System::fileExists(const std::string& fileName) {
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer) == 0);
}

// Improved readFile function with file existence check and retry mechanism
std::string System::readFile(const std::string fileName, int lineNum, bool getLine, bool extractionOperator) {
    const int maxRetries = 5;
    int attempt = 0;
    std::string identifier{};

    while (attempt < maxRetries) {
        if (fileExists(fileName)) {
            std::ifstream in_file(fileName, std::ios::in);
            if (in_file.is_open()) {
                if (getLine) {
                    for (int i = 0; i < lineNum; i++) {
                        std::getline(in_file, identifier);
                    }
                } else if (extractionOperator) {
                    for (int i = 0; i < lineNum; i++) {
                        in_file >> identifier;
                    }
                }
                in_file.close();
                return identifier;
            } else {
                std::cerr << "Error: Could not open file " << fileName << " on attempt " << attempt + 1 << std::endl;
            }
        } else {
            std::cerr << "Error: File does not exist " << fileName << " on attempt " << attempt + 1 << std::endl;
        }
        attempt++;
    }
    std::cerr << "Error: Failed to open file " << fileName << " after " << maxRetries << " attempts." << std::endl;
    return "";
}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    cpu_.User(std::stoll(readFile("/proc/stat", 2, false, true)));
    cpu_.Nice(std::stoll(readFile("/proc/stat", 3, false, true)));
    cpu_.System(std::stoll(readFile("/proc/stat", 4, false, true)));
    cpu_.Idle(std::stoll(readFile("/proc/stat", 5, false, true)));
    cpu_.IOwait(std::stoll(readFile("/proc/stat", 6, false, true)));
    cpu_.IRQ(std::stoll(readFile("/proc/stat", 7, false, true)));
    cpu_.SoftIRQ(std::stoll(readFile("/proc/stat", 8, false, true)));
    cpu_.Steal(std::stoll(readFile("/proc/stat", 9, false, true)));

    // Calculate the total time and update it
    cpu_.TotalTime(cpu_.User() + cpu_.Nice() + cpu_.System() + cpu_.Idle() + cpu_.IOwait() + cpu_.IRQ() + cpu_.SoftIRQ() + cpu_.Steal());

    return cpu_;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    std::string memTotalStr = readFile("/proc/meminfo", 2, false, true);
    std::string memFreeStr = readFile("/proc/meminfo", 5, false, true);
    
    float memTotalF = std::stof(memTotalStr);
    float memFreeF = std::stof(memFreeStr);

    memTotalF = memTotalF / 1000000.0f; // Convert from KB to GB
    memFreeF = memFreeF / 1000000.0f; // Convert from KB to GB

    float usedMemory = memTotalF - memFreeF;
    return (usedMemory / memTotalF)/ 10.0f;
}

// TODO: Return the system's uptime
long System::UpTime() {  
    std::string uptimeStr = readFile("/proc/uptime", 1, false, true);
    long uptime = std::stol(uptimeStr.substr(0, uptimeStr.find(" ")));
    return uptime;
}

// TODO: Return the total number of processes
int System::TotalProcesses() { 
    return FindValueViaKey<int>("/proc/stat", "processes");
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return FindValueViaKey<int>("/proc/stat", "procs_running");
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return readFile("/proc/version", 3, false, true);
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return readFile("/etc/os-release", 5, true, false);
}

// TODO: Return a container composed of the system's processes
std::vector<Process>& System::Processes() {
    procsVec.clear();  // Clear the existing processes

    vector<int> pids = LinuxParser::Pids();

    for (int pid : pids) {
        // Check if the /proc/[pid] directory exists
        std::string procPath = "/proc/" + std::to_string(pid);
        if (!System::fileExists(procPath)) {
            std::cerr << "Process with PID " << pid << " does not exist or has terminated.\n";
            continue;  // Skip this PID
        }

        // Create Process object and add it to the list if valid
        procsVec.emplace_back(pid);
    }

    return procsVec;  // Return by reference
}


// TODO: Find username by UID
std::string System::findUsernameByUID(const std::string &filePath, int uid) {
    std::ifstream passwdFile(filePath);
    std::string line;
    
    if (!passwdFile.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return "";
    }
    
    while (std::getline(passwdFile, line)) {
        std::stringstream ss(line);
        std::string username, x, uidStr;
        int fileUID;
        
        std::getline(ss, username, ':');
        
        // Skip the x field
        std::getline(ss, x, ':');
        
        std::getline(ss, uidStr, ':');
        fileUID = std::stoi(uidStr);
        
        if (fileUID == uid) {
            passwdFile.close();
            return username;
        }
    }
    
    passwdFile.close();
    return ""; 
}

