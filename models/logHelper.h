// loghelper.h
#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <fstream>
#include <string>
#include <iomanip>


//permet d'ecrire des logs
class LogHelper {
public:
    static void WriteLog(const std::string& message);
    static void Debug();
};

#endif // LOGHELPER_H
