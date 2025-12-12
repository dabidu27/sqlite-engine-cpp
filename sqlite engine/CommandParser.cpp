
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CommandParser.h"
#include "StringUtils.h"
#include "CommandType.h"
#include <cstring>
#include <string>
#include "DataTypes.h"
#include <regex>
#include "Table.h"
#include "CommandFileProcessor.h"
#include "Row.h"

CommandParser::CommandParser(const std::string command) {

	this->command = command;
	this->tokens = nullptr;
	this->n_tokens = 0;
	this->type = UNKNOWN_CMD;
	this->valid = false;
}

CommandType CommandParser::recognizeCommand() {

	std::string copy = this->command;
	StringUtils::toUpper(copy);

	//remove blank spaces at the beggining of the command if they exist
	while (!copy.empty() && copy[0] == ' ')
		copy.erase(0, 1); //erases one character starting from position 0

	//.find() returns the position at which a substring begins
	// comment
	if (copy.find("CREATE TABLE") == 0)
		return CREATE_TABLE_CMD;
	else if (copy.find("CREATE INDEX") == 0)
		return CREATE_INDEX_CMD;
	else if (copy.find("DROP TABLE") == 0)
		return DROP_TABLE_CMD;
	else if (copy.find("DROP INDEX") == 0)
		return DROP_INDEX_CMD;
	else if (copy.find("DISPLAY TABLE") == 0)
		return DISPLAY_TABLE_CMD;
	else if (copy.find("INSERT") == 0)
		return INSERT_CMD;
	else if (copy.find("SELECT") == 0)
		return SELECT_CMD;
	else if (copy.find("UPDATE") == 0)
		return UPDATE_CMD;
	else if (copy.find("DELETE") == 0)
		return DELETE_CMD;
	else
		return UNKNOWN_CMD;
}

void CommandParser::tokenizeCommand() {

	//loop through the command chars
	//is space => skip
	//if "( or ) or " or , => add them as a token
	//if between " " or a number or underscore add as a token

	StringUtils::toUpper(this->command);
	std::string* copy = new std::string[100];
	int i = 0;
	int z = 0;
	std::string current_string = "";

	while (i < this->command.size()) {

		if (this->command[i] == ' ')
		{
			if (!current_string.empty()) {
				copy[this->n_tokens] = current_string;
				this->n_tokens++;
				current_string.clear();
			}
			i++;
			continue;
		}
		if (this->command[i] == '"' || this->command[i] == '(' || this->command[i] == ')' || this->command[i] == ',' || this->command[i] == '=' || this->command[i] == '\'')
		{
			if (!current_string.empty()) {
				copy[this->n_tokens] = current_string;
				this->n_tokens++;
				current_string.clear();
			}
			copy[this->n_tokens] = std::string(1, this->command[i]);
			this->n_tokens++;

			i++;
			continue;

		}

		else
		{
			current_string.push_back(this->command[i]);
			i++;
		}

	}

	if (!current_string.empty()) {
		copy[this->n_tokens] = current_string;
		this->n_tokens++;
		current_string.clear();
	}

	this->tokens = new std::string[this->n_tokens];
	for (int i = 0; i < this->n_tokens; i++)
		this->tokens[i] = copy[i];
	delete[] copy;
}

std::string* CommandParser::getTokens() {

	std::string* copy = new std::string[this->n_tokens];
	for (int i = 0; i < this->n_tokens; i++)
		copy[i] = this->tokens[i];
	return copy;

}

int CommandParser::getNoTokens() {
	return this->n_tokens;
}

bool CommandParser::validateCreateTable() {

	std::regex createTablePattern(
		R"(^\s*CREATE\s+TABLE\s+[A-Za-z_]\w*)"
		R"((?:\s+IF\s+NOT\s+EXISTS)?\s*)"
		R"(\(\s*\([A-Za-z_]\w*\s*,\s*(INTEGER|TEXT|FLOAT)\s*,\s*\d+\s*,\s*(\d+|'[^']*')\s*\))"
		R"((?:\s*,\s*\([A-Za-z_]\w*\s*,\s*(INTEGER|TEXT|FLOAT)\s*,\s*\d+\s*,\s*(\d+|'[^']*')\s*\))*\s*\)$)"
	);

	if (std::regex_match(this->command, createTablePattern)) {

		std::cout << std::endl << "CREATE TABLE command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid CREATE TABLE syntax";
		return false;
	}
	
}

bool CommandParser::validateCreateIndex() {
	std::regex createIndexPattern(R"(^\s*CREATE\s+INDEX\s+[A-Za-z_][A-Za-z0-9_]*\s+ON\s+[A-Za-z_][A-Za-z0-9_]*\s*\(\s*[A-Za-z_][A-Za-z0-9_]*\s*\)\s*$)");

	if (std::regex_match(this->command, createIndexPattern)) {
		std::cout << std::endl << "Create index command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
		return false;
	}
}

bool CommandParser::validateDropTable() {

	std::regex dropTablePattern(R"(^\s*DROP\s+TABLE\s+\w+\s*$)");

	if (std::regex_match(this->command,dropTablePattern)) {
		std::cout << std::endl << "DROP TABLE command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid DROP TABLE syntax";
		return false;
	}
}

bool CommandParser::validateDropIndex() {
	std::regex dropIndexPattern(R"(^\s*DROP\s+INDEX\s+[A-Za-z_][A-Za-z0-9_]*\s*$)");

	if (std::regex_match(this->command, dropIndexPattern)) {
		std::cout << std::endl << "DROP INDEX command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Error: Invalid DROP INDEX syntax";
		return false;
	}
}

bool CommandParser::validateDisplayTable() {

	std::regex displayTablePattern(R"(^\s*DISPLAY\s+TABLE\s+\w+\s*$)");

	if (std::regex_match(this->command, displayTablePattern))
	{
		std::cout << std::endl << "DISPLAY TABLE command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid DISPLAY TABLE syntax";
		return false;
	}
}
bool CommandParser::validateInsert()
{
	std::string copy = this->command;
	std::regex insertRegex(R"(^\s*INSERT\s+INTO\s+[A-Za-z_][A-Za-z0-9_]*\s+VALUES\s*\(\s*([0-9]+\.*[0-9]*|\"[A-Za-z_]+\")(\s*,\s*([0-9]+\.*[0-9]*|\"[A-Za-z_]+\"))*\s*\)\s*$)");

	if (std::regex_match(copy, insertRegex)) {

		std::cout << std::endl << "Insert command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid INSERT command";
		return false;
	}

}

bool CommandParser::validateDeleteTable() {

	std::string copy = this->command;
	std::regex deleteTableRegex(R"(^\s*DELETE\s+FROM\s+[A-Za-z_][A-Za-z0-9_]*\s+WHERE\s+\w+\s+=\s+([0-9]+\.*[0-9]*|\"[A-Za-z_]+\")\s*$)");

	if (std::regex_match(copy, deleteTableRegex)) {

		std::cout << std::endl << "DELETE FROM command looks valid";
		return true;
	}
	else {

		std::cout << std::endl << "Invalid DELETE FROM syntax";
		return false;
	}

}

bool CommandParser::validateSelect() {

	std::regex selectRegex(R"(^\s*SELECT\s+(ALL|\(\s*(\*|[A-Za-z_][A-Za-z0-9_]*(\s*,\s*[A-Za-z_][A-Za-z0-9_]*)*)\s*\))\s+FROM\s+[A-Za-z_][A-Za-z0-9_]*(?:\s+WHERE\s+\w+\s+=\s+([0-9]+\.*[0-9]*|\"[A-Za-z_]+\"))?\s*$)");

	if (std::regex_match(this->command, selectRegex)) {

		std::cout << std::endl << "SELECT command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid SELECT syntax";
		return false;
	}
}

bool CommandParser::validateUpdate() {

	std::regex updateRegex(R"(^\s*UPDATE\s+[A-Za-z_][A-Za-z0-9_]*\s+SET\s+[A-Za-z_][A-Za-z0-9_]*\s+=\s+([0-9]+\.*[0-9]*|\"[A-Za-z_]+\")\s+WHERE\s+[A-Za-z_][A-Za-z0-9_]*\s+=\s+([0-9]+\.*[0-9]*|\"[A-Za-z_]+\")\s*$)");

	if (std::regex_match(this->command, updateRegex)) {

		std::cout << std::endl << "UPDATE command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid UPDATE syntax";
		return false;
	}
}


bool CommandParser::validateCommand() {

	std::string copy = this->command;
	CommandType type = recognizeCommand();

	switch (type) {

		case CREATE_TABLE_CMD:
			return validateCreateTable();
		case CREATE_INDEX_CMD:
			return validateCreateIndex();
		case DROP_TABLE_CMD:
			return validateDropTable();
		case DROP_INDEX_CMD:
			return validateDropIndex();
		case DISPLAY_TABLE_CMD:
			return validateDisplayTable();
		case INSERT_CMD:
			return validateInsert();
		case DELETE_CMD:
			return validateDeleteTable();
		case SELECT_CMD:
			return validateSelect();
		case UPDATE_CMD:
			return validateUpdate();


		default:
			std::cout << std::endl << "Error: Unknown or unsupported command";
			return false;
	}

}

void CommandParser::runCommand(Database& db) {

	this->type = this->recognizeCommand();
	this->tokenizeCommand();
	this->valid = this->validateCommand();
	if(this->valid) {

		switch (this->type) {

		case CREATE_TABLE_CMD:
		{
			int sameTable = 0;
			Table* tables = db.getTables();
			for(int i = 0; i < db.getNoTables(); i++)
				if (tables[i].getTableName() == tokens[2])
				{
					sameTable = 1;
					if (tokens[3] == "IF")
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

			break;
		}

		case DROP_TABLE_CMD:
		{
			db.deleteTable(tokens[2]);
			db.deleteTableFile(tokens[2]);
			break;
		}

		case DISPLAY_TABLE_CMD: 
		{
			db.displayTable(tokens[2]);
			break;
		}

		case INSERT_CMD:
		{
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
						db.modifyTableAtIndex(foundTable, row);
						std::string filename = tableName + ".bin";
					}

				}

			}
			break;
		}

		default:

			std::cout << std::endl << "Command not suported yet";
			break;
		}

	}
}

CommandParser::~CommandParser() {

	if (this->tokens != nullptr) {
		delete[] this->tokens;
		this->tokens = nullptr;
	}
}

void CommandParser::processCommandFile(const std::string& filename, Database& db) {
	CommandFileProcessor::processCommandFile(filename, db);
}

bool CommandParser::processDefaultCommandFiles(Database& db) {
	return CommandFileProcessor::processDefaultCommandFiles(db);
}