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
		void display();
		~Database();
		bool operator==(const Database& other);

		explicit operator int();

		void writeTabelsMetadata(std::ofstream& file);
		void readTablesMetadata(std::ifstream& file);
		void printReadTablesMetadata(std::ifstream& file);
};

void operator<< (std::ostream& console, Database& db);