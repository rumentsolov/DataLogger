#ifndef PROCESS_H
#define PROCESS_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstring>

#include "Record.h"
#include "Record.cpp"
#include "ComInit.h"
#include "ActionLogger.h"
#include "GlobalVariables.h"


double voltageLine12AVG;       // Average voltage between line 1 and 2
double voltageLine23AVG;       // Average voltage between line 2 and 3
double voltageLine31AVG;       // Average voltage between line 3 and 1
double currentLine1AVG;        // Average current in line 1
double currentLine2AVG;        // Average current in line 2
double currentLine3AVG;        // Average current in line 3
double combinatedPowerAVG;     // Average combinated power factor for line 1+2+3
double activePowerAVG;         // Average combinated active power for line 1+2+3
double reactivePowerAVG;       // Average combinated reactive power for line 1+2+3
double apparentPowerAVG;       // Average combinated apparent power for line 1+2+3
double calculatedPowerAVG;     // Average combinated calculated power for line 1+2+3


void writeToFL(std::string totalString, const char* newFile) {
    std::fstream file;
    file.open(newFile, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::ofstream out(newFile);
    }
    else
    {

        file << totalString << std::endl << std::endl;
        file.close();
    }
}

void operateTXTFile() { // Since sometimes provides me errors when working with csv file I anyway have to create raw text file by requirements and I use that file to analyze the data

   
   ActionSave(recordFileString);

    std::vector<Record> newRecords; // the records will be stored as objecs here in this vector for easy work

    int counter = 0; // counts the rows readed from the input file

    std::ifstream rawTxtFile;
    rawTxtFile.open(rawFile);
    std::string line;
    int startUpCurrent = 0; // this will indicate if the current is the Startup -> every first record after 0.00 in current is startup

    double line1tmp , line2tmp , line3tmp ;

    line1tmp = line2tmp = line3tmp = 15.00;

    while (getline(rawTxtFile, line)) // its easy and better to read  and process with my own txt file 
    {
        counter++;
        if (counter > 2) { // skipping first 2 rows from file

            for (int i = 0; i < line.size(); i++) if (line[i] == ',') line[i] = ' ';

            std::stringstream sStr(line);
            std::string dateDtmp, timeDtmp;
            std::string id;                     // id inside the table controller record
            int controllerId;                   // serial number of the record inside the controller
            int year;                           // year record is created
            std::string month;                  // month record is created
            std::string day;                    // day record is created
            std::string hour;                   // hour record is created
            std::string minute;                 // minute record is created
            std::string second;                 // second record is created

            double voltageLine12;       // voltage between line 1 and 2
            double voltageLine23;       // voltage between line 2 and 3
            double voltageLine31;       // voltage between line 3 and 1
            double currentLine1;        // current in line 1
            double currentLine2;        // current in line 2
            double currentLine3;        // current in line 3
            double combinatedPower;     // combinated power factor for line 1+2+3
            double activePower;         // combinated active power for line 1+2+3
            double reactivePower;       // combinated reactive power for line 1+2+3
            double apparentPower;       // combinated apparent power for line 1+2+3 , WHEN IT IS "-" POSSITION DOWN
            double calculatedPower = 0; // combinated calculated power for line 1+2+3

            // skipping id & controllerId
            sStr >> id >> controllerId >> dateDtmp;

            for (int i = 0; i < dateDtmp.size(); i++) if (dateDtmp[i] == '/') dateDtmp[i] = ' ';
            std::stringstream sStrDate(dateDtmp);

            sStrDate >> day >> month >> year;

            sStr >> timeDtmp;

            for (int i = 0; i < timeDtmp.size(); i++) if (timeDtmp[i] == ':') timeDtmp[i] = ' ';
            std::stringstream sStrTime(timeDtmp);

            sStrTime >> hour >> minute >> second;

            sStr.precision(2);

            sStr >> voltageLine12 >> voltageLine23 >> voltageLine31 >> currentLine1 >> currentLine2 >> currentLine3 >> combinatedPower >> activePower >> reactivePower >> apparentPower;
            //sStr >> calculatedPowtmp;

            int i = newRecords.size();

            if (i == 1) {
                line1tmp = currentLine1;
                line2tmp = currentLine2;
                line3tmp = currentLine3;
            }

            if (
                line1tmp * startupCurrentFactor > currentLine1 &&
                line2tmp * startupCurrentFactor > currentLine2 &&
                line3tmp * startupCurrentFactor > currentLine3 &&

                line1tmp / startupCurrentFactor < currentLine1 &&
                line2tmp / startupCurrentFactor < currentLine2 &&
                line3tmp / startupCurrentFactor < currentLine3
                )
            {

                if (currentLine1 != 0.00 && currentLine2 != 0.00 && currentLine3 != 0.00 && startUpCurrent >= 1)
                {
                    Record curRecord(id, controllerId, year, month, day, hour, minute, second, voltageLine12, voltageLine23, voltageLine31, currentLine1, currentLine2, currentLine3, combinatedPower, activePower, reactivePower, apparentPower, 0);
                    startUpCurrent++;
                    newRecords.push_back(curRecord);
                }
                else if (currentLine1 == 0.00 && currentLine2 == 0.00 && currentLine3 == 0.00)
                    startUpCurrent = 0;
                else if (currentLine1 != 0.00 && currentLine2 != 0.00 && currentLine3 != 0.00 && startUpCurrent == 0)
                    startUpCurrent++;


                voltageLine12AVG += voltageLine12;
                voltageLine23AVG += voltageLine23;
                voltageLine31AVG += voltageLine31;

                currentLine1AVG += currentLine1;
                currentLine2AVG += currentLine2;
                currentLine3AVG += currentLine3;

                line1tmp = currentLine1;
                line2tmp = currentLine2;
                line3tmp = currentLine3;


                combinatedPowerAVG += combinatedPower;
                activePowerAVG += activePower;
                reactivePowerAVG += reactivePower;
                apparentPowerAVG += apparentPower;
            }
            
                
        }
    }


    std::ostringstream osTr;
    osTr << std::fixed;
    osTr << std::setprecision(2);
 
        // FINDS THE AVARAGE VALUES FROM OBJECTS

    voltageLine12AVG /= newRecords.size();
    voltageLine23AVG /= newRecords.size();
    voltageLine31AVG /= newRecords.size();

    currentLine1AVG /= newRecords.size();
    currentLine2AVG /= newRecords.size();
    currentLine3AVG /= newRecords.size();

    combinatedPowerAVG /= newRecords.size();
    activePowerAVG /= newRecords.size();
    reactivePowerAVG /= newRecords.size();
    apparentPowerAVG /= newRecords.size() ;

  

    osTr <<
        "AVG Voltage 1-2 :" << 
        voltageLine12AVG << 'V'<< std::endl <<
        "AVG Voltage 2-3 :" << 
        voltageLine23AVG << 'V'<< std::endl <<
        "AVG Voltage 3-1 :" << 
        voltageLine31AVG << 'V'<< std::endl <<
        "AVG Current Line 1 :" << 
        currentLine1AVG << 'A' << std::endl <<
        "AVG Current Line 2 :" <<
        currentLine2AVG << 'A' << std::endl <<
        "AVG Current Line 3 :" << 
        currentLine3AVG << 'A' << std::endl <<
        "AVG Combinated Power :" <<
        combinatedPowerAVG << 'W' << std::endl <<
        "AVG Active Power :" <<
        activePowerAVG << 'W' << std::endl <<
        "AVG Apparent Power :" <<
        apparentPowerAVG << 'W' << std::endl << std::endl;


    for (int i = 0; i < newRecords.size(); i++) {
        newRecords[i].valuesSendToStream(osTr);
    }



    writeToFL(osTr.str(), recordFile);

   /* delete[] rawFile;
    rawFile = nullptr;
    delete[] recordFile;
    recordFile = nullptr;*/

    return;
}

#endif 
