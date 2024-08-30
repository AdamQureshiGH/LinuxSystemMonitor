#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <optional>
#include <fstream>
#include <iostream>
#include <sstream>
#include "process.h"
#include "processor.h"
#include <set>

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp
  
 static std::string readFile(std::string fileName, int lineNum, bool getLine, bool extractionOperator);
//static std::string readFile(const std::string& fileName, int lineNum, bool getLine, bool extractionOperator);
  static std::string findUsernameByUID(const std::string &filePath, int uid);
    static unsigned long long safeStoll(const std::string& str);
//I put the definition in the .h fiel so the conpiler already knows 
  static bool isStringValidForStoll(const std::string& str);  // Ensure this is declared in system.h
  static bool fileExists(const std::string& fileName);  // Declare fileExists here if its private

template <typename T>
static T FindValueViaKey(const std::string& fileName, const std::string& keyName, const T& defaultValue = T()) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return defaultValue;
    }

    std::string line;
    T value = defaultValue;  // Initialize the return value with a default value

    while (std::getline(file, line)) {
        std::istringstream linestream(line);
        std::string key;
        linestream >> key;

        if (key == keyName) {
            if (linestream >> value) {
                return value;  // Return the found value
            } else {
                std::cerr << "Error: Failed to extract value for key " << keyName << std::endl;
                return defaultValue;
            }
        }
    }

    std::cerr << "Error: Key " << keyName << " not found in file " << fileName << std::endl;
    return defaultValue;
}
  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  //std::vector<Process> processes_ = {};
  std::vector<Process> procsVec;
};

#endif