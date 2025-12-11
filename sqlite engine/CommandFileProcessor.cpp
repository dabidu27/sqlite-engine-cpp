#include "CommandFileProcessor.h"
#include "CommandParser.h"
#include <fstream>
#include <iostream>
#include <regex>

void trimString(std::string& s) {
    s = std::regex_replace(s, std::regex("^\\s+|\\s+$"), "");
}

void CommandFileProcessor::processCommandFile(const std::string& filename, Database& db) {

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(inFile, line)) {
        trimString(line);
        CommandParser parser(line);
        parser.runCommand(db);
    }
    inFile.close();
}

bool CommandFileProcessor::processDefaultCommandFiles(Database& db) {

    const char* defaultFiles[5] = {
        "commands.txt",
        "commands2.txt",
        "commands3.txt",
        "commands4.txt",
        "commands5.txt"
    };

    bool processed = false;
    for (int i = 0; i < 5; ++i) {
        std::ifstream test(defaultFiles[i]);
        if (test.is_open()) {
            test.close();
            processCommandFile(std::string(defaultFiles[i]), db);
            processed = true;
        }
    }
    return processed;
}