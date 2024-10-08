#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "system.h"
#include "linux_parser.h"
#include <optional>
#include <fstream>
#include <iostream>
#include <sstream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { return 0; }

// TODO: Read and return the number of jiffies for the system

long LinuxParser::Jiffies() {
    std::string line = System::readFile("/proc/stat", 2, false, true);
    std::istringstream linestream(line);
    long user, nice, system, idle, iowait, irq, softirq, steal;
    linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    return user + nice + system + idle + iowait + irq + softirq + steal;
}


long LinuxParser::ActiveJiffies(int pid) {
    std::string pid_str = std::to_string(pid);
    std::string line = System::readFile("/proc/" + pid_str + "/stat", 14, false, true);
    std::istringstream linestream(line);
    long utime, stime, cutime, cstime;
    linestream >> utime >> stime >> cutime >> cstime;
    return utime + stime + cutime + cstime;
}


// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
    std::string line = System::readFile("/proc/stat", 2, false, true);
    std::istringstream linestream(line);
    long user, nice, system, idle, iowait, irq, softirq, steal;
    linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    return user + nice + system + irq + softirq + steal;
}

long LinuxParser::IdleJiffies() {
    std::string line = System::readFile("/proc/stat", 2, false, true);
    std::istringstream linestream(line);
    long user, nice, system, idle, iowait, irq, softirq, steal;
    linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    return idle + iowait;
}


// TODO: Read and return CPU utilization
std::vector<std::string> LinuxParser::CpuUtilization() {
    std::vector<std::string> cpu_values;
    std::string line = System::readFile("/proc/stat", 2, false, true);
    std::istringstream linestream(line);
    std::string value;

    while (linestream >> value) {
        cpu_values.push_back(value);
    }

    return cpu_values;
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
