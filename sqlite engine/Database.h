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
		void display();
		~Database();
};

void operator<< (std::ostream& console, Database& db);