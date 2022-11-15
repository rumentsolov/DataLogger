#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>   

// GET DATE & TIME ACTION IS DONE IN FORMAT YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// SAVES THE ACTION DESCRIBED BY THE INPUT STRING WITH TIME TO LOCAL FILE
void ActionSave(std::string buff) {

    std::fstream myLogger;

    myLogger.open("LoginActions.txt", std::ios::out | std::ios::app);

    if (!myLogger.is_open()) {
        std::ofstream out(buff);
    }
    else
    {

        myLogger << currentDateTime() << "  " << buff << "\n";
        myLogger.close();
    }
}

#endif 
