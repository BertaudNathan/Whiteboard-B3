#include "logHelper.h"

void LogHelper::WriteLog(const std::string& message) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        logFile << std::put_time(&tm, "%H:%M:%S") << " : " << message << std::endl;
        logFile.close();
    }
}

void LogHelper::Debug() {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << "message" << std::endl;
        logFile.close();
    }
}