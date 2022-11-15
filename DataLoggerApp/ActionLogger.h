#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

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

void LoginActionSave(std::string buff) {

    std::ofstream myLink;
    myLink.open("LoginActions.txt");
    myLink << currentDateTime() << "  " << buff << std::endl;
    myLink.close();
}


#endif 
