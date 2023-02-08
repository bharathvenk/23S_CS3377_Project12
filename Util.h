//
// Created by erik on 2/2/21.
//

#ifndef INC_21S_CS3377_PROJECT_UTIL_H
#define INC_21S_CS3377_PROJECT_UTIL_H


#include <ctime>

struct EntryInfo {
    int itemID;
    char itemName[50];
    int quantity;
    float price;
    float weight;
};

class Util {
public:
    const static char* inputFilename;
    const static char* outputFilename;
};


#endif //INC_21S_CS3377_PROJECT_UTIL_H
