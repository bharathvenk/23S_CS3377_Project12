#include "Project1SimpleFileModifier.h"
#include "FileModifyException.h"
#include "Util.h"

#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

// open
void Project1SimpleFileModifier::modifyAndCopyFile(const char* sourceFile, const char* destFile) {
    // Open input file
    int sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1) {
        throw FileModifyException("Error opening source file.");
    }

    // Open output
    int destFd = open(destFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (destFd == -1) {
        close(sourceFd);
        throw FileModifyException("Error creating destination file.");
    }

    // Copying entries
    EntryInfo entry;
    ssize_t bytesRead;
    int entryCount = 0;
    while ((bytesRead = read(sourceFd, &entry, sizeof(EntryInfo))) > 0) {
        // Update the first entry with the specified changes
        if (entryCount == 0) {
            entry.price = 1000000;
            entry.weight = 2.25;
            strncpy(entry.itemName, "CS 3377", sizeof(entry.itemName));
        }

        // Write each entry to the destination file
        ssize_t bytesWritten = write(destFd, &entry, sizeof(EntryInfo));
        if (bytesWritten == -1 || bytesWritten < sizeof(EntryInfo)) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing to output file.");
        }
        entryCount++;
    }
    EntryInfo newEntry = {
            .itemID = 6530927,
            .quantity = 77,
            .price = 89.99,
            .weight = 3.0
    };
    strncpy(newEntry.itemName, "Advanced Programming in the UNIX Environment by Stevens and Rago", sizeof(newEntry.itemName));

    ssize_t bytesWritten = write(destFd, &newEntry, sizeof(EntryInfo));
    if (bytesWritten == -1 || bytesWritten < sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing to output file.");
    }

    // Close both files
    close(sourceFd);
    close(destFd);

    // Print edited entries
    std::cout << "Modified entries:\n";
    destFd = open(destFile, O_RDONLY);
    if (destFd == -1) {
        throw FileModifyException("Error opening destination file.");
    }
    entryCount = 0;
    while (read(destFd, &entry, sizeof(EntryInfo)) > 0) {
        std::cout << "Item ID: " << entry.itemID << ", Name: " << entry.itemName << ", Quantity: " << entry.quantity
                  << ", Price: " << entry.price << ", Weight: " << entry.weight << "\n";
        entryCount++;
    }
    std::cout << "Total number of entries: " << entryCount << std::endl;
}
