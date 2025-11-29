#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CommandParser.h"
#include "StringUtils.h"
#include "CommandType.h"
#include <cstring>
#include <string>
#include "DataTypes.h"
#include <regex>

CommandParser::CommandParser(const std::string command) {

	this->command = command;
	this->tokens = nullptr;
	this->n_tokens = 0;
}

CommandType CommandParser::recognizeCommand() {

	std::string copy = this->command;
	StringUtils::toUpper(copy);

	//remove blank spaces at the beggining of the command if they exist
	while (!copy.empty() && copy[0] == ' ')
		copy.erase(0, 1); //erases one character starting from position 0

	//.find() returns the position at which a substring begins
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

//bool CommandParser::validateCreateIndex() {
//
//	std::string copy = this->command;
//	int n_tokens = 0;
//	char** tokens = tokenizeCommand(n_tokens);
//
//	if (n_tokens < 6) {
//
//		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
//		return false;
//	}
//
//	if (strcmp(tokens[0], "CREATE") != 0 || strcmp(tokens[1], "INDEX") != 0) {
//
//		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
//		return false;
//	}
//
//	char* index_name = tokens[2];
//	if (strcmp(index_name, "ON") == 0) {
//
//		std::cout << std::endl << "Error: Missing index name";
//		return false;
//	}
//
//	if (strcmp(tokens[3], "ON") != 0) {
//
//		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
//		return false;
//	}
//
//	char* table_name = tokens[4];
//	if (strchr(table_name, '(') != nullptr || strchr(table_name, ')') != nullptr) {
//
//		std::cout << std::endl << "Error: Missing table name";
//		return false;
//	}
//
//	char* column = tokens[5];
//	if (strchr(column, '(') == 0 || strchr(column, ')') == nullptr) {
//
//		std::cout << std::endl << "Error: Missing paranthesis";
//		return false;
//	}
//
//	std::cout << std::endl << "Create index command looks valid";
//	std::cout << std::endl << "Index name: " << index_name;
//	std::cout << std::endl << "Table name: " << table_name;
//	std::cout << std::endl << "Column name: " << column;
//
//	for (int i = 0; i < n_tokens; i++) {
//		delete[] tokens[i];
//	}
//	delete[] tokens;
//
//	return true;
//
//
//}
//
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
//
//bool CommandParser::validateDropIndex() {
//
//	std::string copy = this->command;
//	int n_tokens = 0;
//	char** tokens = tokenizeCommand(n_tokens);
//
//	if (n_tokens < 3) {
//		std::cout << std::endl << "Error: Invalid DROP INDEX syntax";
//		return false;
//	}
//
//	if (strcmp(tokens[0], "DROP") != 0 || strcmp(tokens[1], "INDEX") != 0) {
//		std::cout << std::endl << "Error: Invalid DROP INDEX syntax";
//		return false;
//	}
//
//	char* index_name = tokens[2];
//	if (strlen(index_name) == 0 || strchr(index_name, '(') != nullptr || strchr(index_name, ')') != nullptr) {
//		std::cout << std::endl << "Error: Invalid or missing index name";
//		return false;
//	}
//
//	std::cout << std::endl << "DROP INDEX command looks valid";
//	std::cout << std::endl << "Index name: " << index_name;
//
//	for (int i = 0; i < n_tokens; i++)
//		delete[] tokens[i];
//	delete[] tokens;
//
//	return true;
//}
//
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
		//case CREATE_INDEX_CMD:
			//return validateCreateIndex();
		case DROP_TABLE_CMD:
			return validateDropTable();
		//case DROP_INDEX_CMD:
			//return validateDropIndex();
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

CommandParser::~CommandParser() {

	if (this->tokens != nullptr) {
		delete[] this->tokens;
		this->tokens = nullptr;
	}
}