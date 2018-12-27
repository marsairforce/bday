/* bday.cpp
Simple birthday reminder program
Reads data from a specified file
Format:
<date> <name> <memmo>

Displays a notice if a birthday is within 15 days of the system date
TODO: replace string and list classes with c++ standard library classes
TODO: provide support for connection to a DBMS
*/

#include "String.h"
#include "StringParser.h"
#include "Linklist.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>

struct Record {
  String date;    // string format of the date
  String name;    // person's name
  String memo;    // some memo, (what to get them)
  Record() {};
};


const char* monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
const int   monthDays[12]  = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getMonthIndex(String &s) {
  for (int i = 0; i < 12; i++) {
    if (s == monthNames[i]) {
      return i;
    }
  }
  return -1;
}

const char* addS(int v) { return (v == 1)?"":"s"; }
const char* addY(int v) { return (v == 1)?"y":"ies"; }

int main(int argc, char** argv) {

  bool showRecords = false;

        String fileName = argv[1];      // get from parameter
        if (!fileName) {
                std::cerr << "Require birthday data file as first parameter" << std::endl;
                exit(1);
        }
        // open birthday file
        std::ifstream dFile(fileName.cptr());

        if (!dFile.good()) {
                std::cerr << "Could not open input file: " << fileName << std::endl;
                exit(1);
        }
        // read the file into our record format
        // note: the file is a tab delimited format, one record per line
        SingleList<Record> recordList;

        // while not end of file, read the data file into a list
        while (!dFile.eof()) {

                Record* newItem = new Record();
                char temp[81];
                dFile.getline(temp,80);
                if (!strlen(temp)) {      // handles last new line char (if any)
                  break;
                }
                StringParser t(temp);
                newItem->date = t.getNextToken("\t");
                newItem->name = t.getNextToken("\t");
                newItem->memo = t.getNextToken("\t");

                recordList.addEnd(newItem);

        }
        // dump the contents of the list;

        if (showRecords) {
          recordList.goStart();
          for (int i = 0; i < recordList.size(); i++) {
            Record *newItem = recordList.getNext();
            std::cout << "[" << i+1 << "]: d:" << newItem->date << " n:" << newItem->name << " m:" << newItem->memo << std::endl;
          }
        }

        // close file
        dFile.close();

        // get the current date from the system
        char sysTimeString[20];
        time_t tx = time(NULL);
        strftime(sysTimeString,20,"%b %d %Y",localtime(&tx));

        String systemDate = sysTimeString;
        int systemYear = systemDate.right(4).parseInt();

        String systemMonth = systemDate.left(3);
        int systemDay =  systemDate.left(6).right(2).parseInt();
        int monthIndex = getMonthIndex(systemMonth);
        if (monthIndex < 0) {
          std::cerr << "Invalid month input: " << systemMonth;
          return 1;
        }
        // std::cout << "System date is: " << systemDate << " , month:" << systemMonth << " , day:" << systemDay << " , index:" << monthIndex << " , year:" << systemYear << std::endl;

        //std::cout << std::endl << std::endl << std::endl;

        // check each record with current date
        int found = 0;
        recordList.goStart();
        for (int i = 0; i < recordList.size(); i++) {
                Record* item = recordList.getNext();
                String recordMonth = item->date.left(3);
                int recordDay = item->date.left(6).right(2).parseInt();
                // display any ones within 15 days
                // display any ones that are today in red

                if (getMonthIndex(recordMonth) == monthIndex) { // same month

                        if (systemDay == recordDay) { // exact match
                                std::cout << item->name << " has a birthday today!   " << systemYear - item->date.right(4).parseInt() << " years old" << std::endl
                                        << "        Memo: " << item->memo << std::endl << std::endl;
                                found ++;
                        }

                        else if (recordDay - systemDay <= 15 && recordDay-systemDay > 0){
                                std::cout << item->name << " has a birthday in " << recordDay - systemDay << " day" << addS(recordDay - systemDay) << "!   " << systemYear - item->date.right(4).parseInt() << " years old" << std::endl
                                        << "        Memo: " << item->memo << std::endl << std::endl;
                                found ++;
                        }

                }

        }
        // optionally pause a bit
        if (found) {
                std::cout << found << " entr" << addY(found) << "." << std::endl;
                sleep(3);
        }

        //std::cout << "Done" << std::endl;
        // clean up stuff used
        recordList.deleteAll();
}

