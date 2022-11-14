#ifndef TREND_H
#define TREND_H

#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Record.h"
#include "ComInit.h"

const char* rawFile = "C:\\Users\\USER\\Desktop\\rawfile.txt";
const char* recordFile = "C:\\Users\\USER\\Desktop\\record.txt";
const char* inputFile = "https://www.rumentsolov.com/gallery/trend.csv";

void operateTXTFile() {


    int counter = 0;

    std::stringstream myFile(buffer);

    std::string line;
    std::vector<Record> newRecords;
    while (getline(myFile, line))
    {
        counter++;
        if (counter > 2) { // skipping first 2 rows from file

            for (int i = 0; i < line.size(); i++) if (line[i] == ',') line[i] = ' ';
            std::stringstream sStr(line);
            std::string dateDtmp, timeDtmp;
            int id;                     // id inside the table controller record
            int controllerId;           // serial number of the record inside the controller
            int year;                   // year record is created
            int month;                  // month record is created
            int day;                    // day record is created
            int hour;                   // hour record is created
            int minute;                 // minute record is created
            int second;                 // second record is created

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


            if (currentLine1 != 0.00 & currentLine2 != 0.00 & currentLine3 != 0.00)
            {
                Record curRecord(id, controllerId, year, month, day, hour, minute, second, voltageLine12, voltageLine23, voltageLine31, currentLine1, currentLine2, currentLine3, combinatedPower, activePower, reactivePower, apparentPower, calculatedPower);
                newRecords.push_back(curRecord);
            }
        }
    }

    std::ostringstream osTr;

    for (int i = 0; i < newRecords.size(); i++) {
        newRecords[i].sendToStream(osTr);
    }


}

int run()
{

    // OPERATING WITH INFO FROM CSV FILE AND CREATEST RAW TXT FILE TO WORKING WITH

    std::ofstream rawFileStream(rawFile, std::ofstream::binary); // op Stream for raw file

    ComInit init;
    CComPtr<IStream> pStream; // use CComPtr so you don't have to manually call Release()
    HRESULT hr = URLOpenBlockingStreamW(nullptr, L"https://www.rumentsolov.com/gallery/trend.csv", &pStream, 0, nullptr);// Open the HTTP request
    if (FAILED(hr))
    {
        //"ERROR: Could not connect. HRESULT: 0x"
        return 1;
    }

    // Download the response and write it to file.
    char buffer[128];
    do
    {
        DWORD bytesRead = 0;
        hr = pStream->Read(buffer, sizeof(buffer), &bytesRead);



    } while (SUCCEEDED(hr) && hr != S_FALSE);

    if (FAILED(hr))
    {
        //"ERROR: Download failed. HRESULT: 0x"
        return 2;
    }


    //"Job Done!" ;

    return 0;
}


#endif 