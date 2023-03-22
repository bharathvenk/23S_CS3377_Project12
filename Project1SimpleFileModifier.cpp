#include "Project1SimpleFileModifier.h"
#include "FileModifyException.h"
#include "Util.h"
#include <fstream>
#include <iostream>
#include <cstring>

void Project1SimpleFileModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    // Open input file
    std::ifstream input(Util::inputFilename, std::ios::binary);
    if (!input.is_open()) {
        throw FileModifyException("Failed to open input file");
    }

    // Open the file
    std::ofstream output(Util::outputFilename, std::ios::binary);
    if (!output.is_open()) {
        throw FileModifyException("Failed to open output file");
    }

    // Read the entries
    int numEntries;
    input.read(reinterpret_cast<char*>(&numEntries), sizeof(numEntries));

    // Modify the first entry
    EntryInfo firstEntry;
    input.read(reinterpret_cast<char*>(&firstEntry), sizeof(firstEntry));
    firstEntry.price = 1000000.0;
    firstEntry.weight = 2.25;
    strncpy(firstEntry.itemName, "CS 3377", sizeof(firstEntry.itemName));
    output.write(reinterpret_cast<const char*>(&firstEntry), sizeof(firstEntry));

    // Write the entries
    EntryInfo entry;
    for (int i = 1; i < numEntries; i++) {
        input.read(reinterpret_cast<char*>(&entry), sizeof(entry));
        output.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
    }

    // Adding entries
    EntryInfo newEntry;
    newEntry.itemID = 6530927;
    strncpy(newEntry.itemName, "Advanced Programming in the UNIX Environment by Stevens and Rago", sizeof(newEntry.itemName));
    newEntry.quantity = 77;
    newEntry.price = 89.99;
    newEntry.weight = 3.0;
    output.write(reinterpret_cast<const char*>(&newEntry), sizeof(newEntry));
    numEntries++;

    //updating entries
    output.seekp(0, std::ios::beg);
    output.write(reinterpret_cast<const char*>(&numEntries), sizeof(numEntries));
}
