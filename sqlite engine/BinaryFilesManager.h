#pragma once
#include <fstream>
#include "Database.h"
#include <string>

class BinaryFilesManager {

	public:
		static void loadMetadata(Database& db);
		static void writeMetadata(Database& db);
		static void writeTableData(std::string tableName, Database& db);
};