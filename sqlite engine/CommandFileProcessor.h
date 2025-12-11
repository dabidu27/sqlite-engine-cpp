#pragma once

#include <string>
#include "Database.h"

class CommandFileProcessor {
public:
    static void processCommandFile(const std::string& filename, Database& db);
    static bool processDefaultCommandFiles(Database& db);
};