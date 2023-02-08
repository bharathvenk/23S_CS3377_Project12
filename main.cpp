#include <iostream>
#include <unistd.h>
#include <cstring>

#include "Util.h"
#include "FileChecker.h"
#include "FileModifyException.h"
#include "Project1SimpleFileModifier.h"

//---------------------------------------------------------
// Arguments:
// ModifierType: 1-4, corresponds to the project parts
//      1. Simple modifier
//      2. Multiprocess modifier
//      3. Threaded modifier
//      4. IPC (socket) modifier
//
// IOType: required for modifier types 2 and 4, because
//         they use 2 processes (one to read and the other
//         to write). Not needed for modifier types 1 & 3
//
//         For parts 2 & 4, call the read version (2)
//         from CLion. Your code should call the write
//         (3) version for the 2nd process.
//--------------------------------------------------------
int main(int argc, char** argv) {
    // Delete the output file so we're starting fresh
    unlink(Util::outputFilename);

    // Modify it!
    Project1SimpleFileModifier modifier;
    try {
        modifier.modifyAndCopyFile(Util::inputFilename, Util::outputFilename);
    } catch (FileModifyException e) {
        std::cerr << "Error modifying file: " << e.what();
        exit(1);
    } catch ( std::exception e) {
        std::cerr << "Error modifying file: " << e.what();
        exit(1);
    }

    try {
        FileChecker::checkFile();
    } catch (std::exception e) {
        std::cerr << "File doesn't match" << std::endl;
        exit(1);
    }
}
