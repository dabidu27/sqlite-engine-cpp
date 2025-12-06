#pragma once
#include "Table.h"

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
};

void operator<< (std::ostream& console, Database& db);