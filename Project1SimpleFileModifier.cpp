// Import necessary headers
#include "Project1SimpleFileModifier.h"
#include "FileModifyException.h"
#include "Util.h"

#include <iostream>
#include <fstream>
#include <cstring>




#include <fcntl.h>
#include <unistd.h>


// Define function to modify and copy a file
void Project1SimpleFileModifier::modifyAndCopyFile(const char* sourceFile, const char* destFile) {
    // Open
    int sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1) {
        throw FileModifyException("  Error opening source file.");
    }


    std::ofstream destFileStream(destFile);
    if (!destFileStream) {
        close(sourceFd);
        throw FileModifyException("Error creating destination file.");
    }


    char buffer[BUFSIZ];
    ssize_t bytesRead;
    while ((bytesRead = read(sourceFd, buffer, BUFSIZ)) > 0) {
        destFileStream.write(buffer, bytesRead);
    }


    close(sourceFd);
    destFileStream.close();
}





