#include "Database.h"
#include <iostream>

Database::Database() {
	this->tables = nullptr;
	this->noTables = 0;
	std::cout << std::endl << "Database created";
}

void Database::addTable(Table table) {

	Table* copy = new Table[this->noTables + 1];
	for (int i = 0; i < this->noTables; i++)
		copy[i] = this->tables[i];

	copy[this->noTables] = table;

	if (this->tables != nullptr) {
		delete[] this->tables;
		this->tables = nullptr;
	}

	this->tables = copy;
	this->noTables++;

}
Table* Database::getTables() {

	Table* copy = new Table[this->noTables];
	for (int i = 0; i < this->noTables; i++)
		copy[i] = this->tables[i];
	return copy;

}

int Database::getNoTables() {

	return this->noTables;
}

Database::~Database() {

	if (this->tables != nullptr) {

		delete[] this->tables;
		this->tables = nullptr;
	}
}