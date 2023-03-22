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

    // Modify first entry
    EntryInfo entry;
    ssize_t bytesRead = read(sourceFd, &entry, sizeof(EntryInfo));
    if (bytesRead == -1) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error reading input file.");
    }
    if (bytesRead < sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Input file too short.");
    }
    entry.price = 1000000;
    entry.weight = 2.25;
    strncpy(entry.itemName, "CS 3377", sizeof(entry.itemName));

    // Write
    ssize_t bytesWritten = write(destFd, &entry, sizeof(EntryInfo));
    if (bytesWritten == -1 || bytesWritten < sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing to output file.");
    }

    // Copying entries
    char buffer[BUFSIZ];
    while ((bytesRead = read(sourceFd, buffer, BUFSIZ)) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten == -1 || bytesWritten < bytesRead) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing to output file.");
        }
    }

    // Addin
    EntryInfo newEntry = {
            .itemID = 6530927,
            .quantity = 77,
            .price = 89.99,
            .weight = 3.0
    };
    strncpy(newEntry.itemName, "Advanced Programming in the UNIX Environment by Stevens and Rago",
            sizeof(newEntry.itemName));
    bytesWritten = write(destFd, &newEntry, sizeof(EntryInfo));
    if (bytesWritten == -1 || bytesWritten < sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing to output file.");
    }

    // Closing
    close(sourceFd);
    close(destFd);

    // Printing edited entries
    std::cout << "Modified entries:\n";
    sourceFd = open(destFile, O_RDONLY);
    if (sourceFd == -1) {
        throw FileModifyException("Error opening destination file.");
    }
    while (read(sourceFd, &entry, sizeof(EntryInfo)) > 0) {
        std::cout << "Item ID: " << entry.itemID << ", Name: " << entry.itemName << ", Quantity: " << entry.quantity
                  << ", Price: " << entry.price << ", Weight: " << entry.weight << "\n";
    }

}