#include "Project1SimpleFileModifier.h"
#include "FileModifyException.h"
#include "Util.h"

#include <iostream>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
void Project1SimpleFileModifier::modifyAndCopyFile(const char* sourceFile, const char* destFile) {
    // Open input file
    int sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1) {
        throw FileModifyException("Error opening source file.");
    }

    // Open output file for writing
    int destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (destFd == -1) {
        close(sourceFd);
        throw FileModifyException("Error creating destination file.");
    }

    // Read header from source file
    int header;
    int bytesRead = read(sourceFd, &header, sizeof(int));
    if (bytesRead != sizeof(int)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error reading header from source file.");
    }
    std::cout << "Header of source file: " << header << std::endl;
    int newHeader = header + 1;

    // Write header to destination file
    int bytesWritten = write(destFd, &newHeader, sizeof(int));
    if (bytesWritten != sizeof(int)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing header to destination file.");
    }
    std::cout << "Header of destination file: " << newHeader << std::endl;

    // Read the first entry from source file
    EntryInfo firstEntry;
    bytesRead = read(sourceFd, &firstEntry, sizeof(EntryInfo));
    if (bytesRead != sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error reading first entry from source file.");
    }

    // Modify the first entry
    firstEntry.price = 1000000;
    firstEntry.weight = 2.25;
    strncpy(firstEntry.itemName, "CS 3377", 50);

    // Write the modified first entry to destination file
    if (write(destFd, &firstEntry, sizeof(EntryInfo)) != sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing first entry to destination file.");
    }

    // Copy the rest of the entries from source file to destination file
    EntryInfo entry;
    while ((bytesRead = read(sourceFd, &entry, sizeof(EntryInfo))) > 0) {
        if (write(destFd, &entry, bytesRead) != bytesRead) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing to destination file.");
        }
    }
    if (bytesRead < 0) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error reading from source file.");
    }

    // Add a new entry at the end of destination file
    EntryInfo newEntry;
    newEntry.itemID = 6530927;
    strncpy(newEntry.itemName, "Advanced Programming in the UNIX Environment by Stevens and Rago", 49);
    newEntry.quantity = 77;
    newEntry.price = 8999;
    newEntry.weight = 3.0;

    // Write the new entry to destination file
    if (write(destFd, &newEntry, sizeof(EntryInfo)) != sizeof(EntryInfo)) {
        close(sourceFd);
        close(destFd);
        throw FileModifyException("Error writing new entry to destination file.");
    }

    // Close files
    close(sourceFd);
    close(destFd);
}


    // Write the entry to destination file







