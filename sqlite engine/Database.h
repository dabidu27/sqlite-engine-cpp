#pragma once
#include "Table.h"
#include <fstream>

class Database {

	Table* tables = nullptr;
	int noTables = 0;

public:

	Database();
	void addTable(Table table);
	Table* getTables();
	int getNoTables();
	void deleteTable(std::string tableName);
	void displayTable(std::string tableName);
	~Database();
	bool operator==(const Database& other);

	explicit operator int();

	void writeTablesMetadata(std::ofstream& file);
	void readTablesMetadata(std::ifstream& file);
	void printReadTablesMetadata(std::ifstream& file);
	void createTableFile(std::string tableName);
	void deleteTableFile(std::string tableName);
};

void operator<< (std::ostream& console, Database& db);