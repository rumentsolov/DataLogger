#pragma once

#include "ActionLogger.h"
#include "GlobalVariables.h"

class Record {
public:

    std::string id;                     // id inside the table controller record
    int controllerId;           // serial number of the record inside the controller
    int year;                   // year record is created
    std::string month;          // month record is created
    std::string day;            // day record is created
    std::string hour;           // hour record is created
    std::string minute;         // minute record is created
    std::string second;         // second record is created

    double voltageLine12;       // voltage between line 1 and 2
    double voltageLine23;       // voltage between line 2 and 3
    double voltageLine31;       // voltage between line 3 and 1
    double currentLine1;        // current in line 1
    double currentLine2;        // current in line 2
    double currentLine3;        // current in line 3
    double combinatedPower;     // combinated power factor for line 1+2+3
    double activePower;         // combinated active power for line 1+2+3
    double reactivePower;       // combinated reactive power for line 1+2+3
    double apparentPower;       // combinated apparent power for line 1+2+3
    double calculatedPower;     // combinated calculated power for line 1+2+3



    Record();

    Record(std::string id, int controllerId, int year, std::string month, std::string day, std::string hour, std::string minute, std::string second, double voltageLine12, double voltageLine23, double voltageLine31, double currentLine1, double currentLine2, double currentLine3, double combinatedPower, double activePower, double reactivePower, double apparentPower, double calculatedPower) {

        if (id.size() == 3)
            this->id = id;
        else if (id.size() == 2)
            this->id = " "+ id;
        else if (id.size() == 1)
            this->id = "  " + id;
        this->controllerId = controllerId;
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        this->voltageLine12 = voltageLine12;
        this->voltageLine23 = voltageLine23;
        this->voltageLine31 = voltageLine31;
        this->currentLine1 = currentLine1;
        this->currentLine2 = currentLine2;
        this->currentLine3 = currentLine3;
        this->combinatedPower = combinatedPower;
        this->activePower = activePower;
        this->reactivePower = reactivePower;
        this->apparentPower = apparentPower;
        this->calculatedPower = calculatedPower;

    }

    void valuesSendToStream(std::ostringstream& oStr) 
    
    {
        oStr <<
            this->id << ' ' <<
            this->controllerId << ' ' <<
            this->day << '/' <<
            this->month << '/' <<
            (this->year - 2000) << ' ' <<
            this->hour << ':' <<
            this->minute << ':' <<
            this->second << ' ';

        oStr << std::fixed;
        oStr << std::setprecision(2);

        oStr <<
            this->voltageLine12 << 'V' << ' ' <<
            this->voltageLine23 << 'V' << ' ' <<
            this->voltageLine31 << 'V' << ' ' <<
            this->currentLine1 << 'A' << ' ' <<
            this->currentLine2 << 'A' << ' ' <<
            this->currentLine3 << 'A' << ' ' <<
            this->combinatedPower << 'W' << ' ' <<
            this->activePower << 'W' << ' ' <<
            this->reactivePower << 'W' <<
            // calculatedPow[i] << 'W' << ' ';
            std::endl;
    }

};