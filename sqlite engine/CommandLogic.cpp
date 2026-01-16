#include "CommandLogic.h"
#include "CommandType.h"
#include "Database.h"
#include "Table.h"
#include <iostream>


CommandLogic::CommandLogic(std::string* tokens, int n_tokens) {
	
	this->tokens = new std::string[n_tokens];
	for (int i = 0; i < n_tokens; i++)
		this->tokens[i] = tokens[i];
	this->n_tokens = n_tokens;
}

CreateTable::CreateTable(std::string* tokens, int n_tokens) : CommandLogic(tokens, n_tokens) {};

void CreateTable::implementLogic(Database& db) {

	int sameTable = 0;
	Table* tables = db.getTables();
	for (int i = 0; i < db.getNoTables(); i++)
		if (tables[i].getTableName() == this->tokens[2])
		{
			sameTable = 1;
			if (this->tokens[3] == "IF")
			{
				break;
			}
			else {
				//std::cout << std::endl << "Table already exists";
				std::cout << std::endl << "Table " << tables[i].getTableName() << " already exists";
				break;
			}
		}
	delete[] tables;
	tables = nullptr;

	if (sameTable != 1) {

		Table table = Table(tokens, n_tokens);
		db.addTable(table);
		db.createTableFile(tokens[2]);
	}
}

DropTable::DropTable(std::string* tokens, int n_tokens) : CommandLogic(tokens, n_tokens) {};
void DropTable::implementLogic(Database& db) {

	db.deleteTable(tokens[2]);
	db.deleteTableFile(tokens[2]);
}

Insert::Insert(std::string* tokens, int n_tokens) : CommandLogic(tokens, n_tokens) {};
void Insert::implementLogic(Database& db) {

	std::string tableName = tokens[2];
	Table* tables = db.getTables();
	int foundTable = -1;
	for (int i = 0; i < db.getNoTables(); i++)
		if (tables[i].getTableName() == tableName)
		{
			foundTable = i;
			break;
		}
	if (foundTable == -1)
	{
		std::cout << std::endl << "Table does not exist";
		delete[] tables;
		tables = nullptr;
	}

	else {

		int noValues = 0;
		for (int i = 5; i < this->n_tokens - 1; i++)
			if (this->tokens[i] != "," && this->tokens[i] != "'" && this->tokens[i] != "\"")
				noValues++;
		if (noValues < tables[foundTable].getNoColumns())
			std::cout << std::endl << "Too few values";
		else if (noValues > tables[foundTable].getNoColumns()) {
			std::cout << std::endl << "Too many values";
		}
		else {

			std::string* values = new std::string[noValues];
			int j = 0;
			for (int i = 5; i < this->n_tokens - 1; i++)
				if (this->tokens[i] != "," && this->tokens[i] != "'" && this->tokens[i] != "\"")
				{
					values[j] = this->tokens[i];
					j++;
				}
			Columns* columns = tables[foundTable].getColumns();
			int valuesOkay = 1;
			for (int i = 0; i < noValues; i++) {

				if (columns[i].getType() == INTEGER) {

					int convert = 0;
					try {
						convert = std::stoi(values[i]);
					}
					catch (std::invalid_argument e) {
						std::cout << std::endl << "Invalid argument";
						valuesOkay = 0;
					}
				}
			}

			delete[] columns;
			columns = nullptr;
			delete[] tables;
			tables = nullptr;

			if (valuesOkay == 1) {
				Row row(values, noValues);
				db.addRowAtIndex(foundTable, row);
			}

		}

	}
}

int DisplayTable::NO_DISPLAY_COMMANDS = 0;

DisplayTable::DisplayTable(std::string* tokens, int n_tokens) : CommandLogic(tokens, n_tokens) {

	DisplayTable::NO_DISPLAY_COMMANDS++;
};
void DisplayTable::implementLogic(Database& db) {

	db.displayTable(tokens[2]);
	try {
		db.displayTableInFile(tokens[2], this->getNoDisplays());
	}
	catch (std::exception* e) {

		std::cout << std::endl << e->what();
		delete e;
	}
}
std::string DisplayTable::getNoDisplays() {
	return std::to_string(DisplayTable::NO_DISPLAY_COMMANDS);
}

Delete::Delete(std::string* tokens, int n_tokens) : CommandLogic(tokens, n_tokens) {};
void Delete::implementLogic(Database& db) {

	std::string tableName = this->tokens[2];
	int equalPosition = 5;
	std::string leftArg = this->tokens[4];
	std::string rightArg = "";

	if (this->tokens[equalPosition + 1] != "\"")
		rightArg = this->tokens[equalPosition + 1];
	else
		rightArg = this->tokens[equalPosition + 2];

	Table* tables = db.getTables();
	int foundTable = 0;
	int foundColumn = 0;
	int valueOkay = 1;
	for (int i = 0; i < db.getNoTables(); i++)
		if (tables[i].getTableName() == tableName) {

			foundTable = 1;
			Columns* columns = tables[i].getColumns();
			for (int j = 0; j < tables[i].getNoColumns(); j++)
				if (columns[j].getName() == leftArg) {

					foundColumn = 1;
					if (columns[j].getType() == INTEGER) {

						int convert = 0;
						try {
							convert = std::stoi(rightArg);
						}
						catch (std::invalid_argument e) {
							std::cout << std::endl << "Invalid argument";
							valueOkay = 0;
						}
					}

					if (valueOkay != 0) {

						db.deleteRowAtIndex(i, j, rightArg);
					}

					break;


				}

			if (foundColumn == 0)
				std::cout << std::endl << "Column " << leftArg << " not found";

			delete[] columns;
			columns = nullptr;
			break;

		}


	if (foundTable == 0) {
		std::cout << std::endl << "Table " << tableName << " not found";
	}

	delete[] tables;
	tables = nullptr;
}