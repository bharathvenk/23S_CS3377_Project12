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

    // Copying entries


    EntryInfo entry;


    ssize_t bytesRead;
    int entryCount = 0;
    bool firstEntryModified = false;


    while ((bytesRead = read(sourceFd, &entry, sizeof(entry))) > 0) {

        // Update the first entry with the specified changes




        if (entryCount == 0) {

            std::cout << "first entry item ID: " << entry.itemID << std::endl;
            EntryInfo modifiedEntry = {




                    .price = 1000000,
                    .weight = 2.25
            };
            strncpy(modifiedEntry.itemName, "CS 3377", sizeof(modifiedEntry.itemName) - 1);


            entry = modifiedEntry;
            firstEntryModified = true;



        }





        // Write each entry to the destination file
        int oldID = entry.itemID;
        entry.itemID = oldID;
        ssize_t bytesWritten = write(destFd, &entry, sizeof(entry));
        if (bytesWritten == -1 || bytesWritten < sizeof(entry)) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing to output file.");
        }
        entryCount++;
    }


    // Add the new entry to the end of the file if the first entry has been modified
    // Add the new entry to the end of the file if the first entry has been modified
    if (firstEntryModified) {
        EntryInfo newEntry = {
                .itemID = 6530927,
                .quantity = 77,
                .price = 89.99,
                .weight = 3.0
        };
        strncpy(newEntry.itemName, "Advanced Programming in the UNIX Environment by Stevens and Rago", sizeof(newEntry.itemName) - 1);

        // Write the new entry to the destination file
        ssize_t bytesWritten = write(destFd, &newEntry, sizeof(newEntry));
        if (bytesWritten == -1 || bytesWritten < sizeof(newEntry)) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing to output file.");
        }

        // Update the header with the new entry count
        int headerSize = sizeof(entryCount);
        int64_t fileSize = lseek(destFd, 0, SEEK_END);
        if (fileSize == -1) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error seeking to end of output file.");
        }
        lseek(destFd, 0, SEEK_SET);

        // Update the entry count to include the new entry
        entryCount++;

        bytesWritten = write(destFd, &entryCount, headerSize);
        if (bytesWritten == -1 || bytesWritten < headerSize) {
            close(sourceFd);
            close(destFd);
            throw FileModifyException("Error writing header to output file.");
        }
    }


    // Close both files
    close(sourceFd);
    close(destFd);

    // Print edited entries
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

    close(destFd);
}
