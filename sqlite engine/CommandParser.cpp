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

CommandParser::CommandParser(std::string command) {

	this->command = command;
}

CommandType CommandParser::recognizeCommand() {
	
	std::string copy = this->command;
	toUpper(copy);
	
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

char** CommandParser::tokenizeCommand(int& n_tokens) {

	char* copy = new char[this->command.length() + 1];
	toUpper(this->command);
	strcpy(copy, this->command.c_str());


	char* token = strtok(copy, " ");
	while (token){
		
		n_tokens++;
		token = strtok(nullptr, " ");
	}

	char** tokens = new char* [n_tokens];

	strcpy(copy, this->command.c_str());
	token = strtok(copy, " ");
	int i = 0;
	while (token && i < n_tokens) {
		
		tokens[i] = new char[strlen(token) + 1];
		strcpy(tokens[i], token);
		token = strtok(nullptr, " ");
		i++;
	}
	
	delete[] copy;
	copy = nullptr;
	return tokens;
}

bool CommandParser::validateCreateTable() {

	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);

	if (n_tokens < 4) {
		std::cout <<std::endl<< "Error: Invalid CREATE TABLE syntax.";
		return false;
	}
	
	if (strcmp(tokens[0], "CREATE") != 0 || strcmp(tokens[1], "TABLE") != 0) {

		std::cout << std::endl << "Error: Invalid CREATE TABLE syntax";
		return false;
	}

	if (strchr(tokens[2], '(') != nullptr || strchr(tokens[2], ')') != nullptr || strchr(tokens[2], ',') != nullptr) {

		std::cout << std::endl << "Error: Invalid table name";
		return false;
	}

	if (strchr(tokens[3], '(') == nullptr || strchr(tokens[n_tokens-1], ')') == nullptr) {
		
		std::cout << std::endl << "Error: Missing paranthesis";
		return false;
	}

	for (int i = 3; i < n_tokens - 1; i = i + 2) {

		if (strchr(tokens[i], ',') != nullptr) {
			std::cout << std::endl << "Error: Unexpected comma";
			return false;
		}
	}

	int n_columns = 0;
	for (int i = 4; i < n_tokens - 1; i = i + 2) {

		n_columns++;
		if (strchr(tokens[i], ',') == nullptr) {
			std::cout << std::endl << "Error: Expected comma";
			return false;
		}

		DataType type = getDataFromString(tokens[i]);
		if (type == UNKNOWN_DATA_TYPE) {
			std::cout << std::endl << "Error: Unknown data type";
			return false;
		}
	}

	DataType type = getDataFromString(tokens[n_tokens - 1]);
	if (type == UNKNOWN_DATA_TYPE) {
		std::cout << std::endl << "Error: Unknown data type";
		return false;
	}
	else
		n_columns++;


	std::cout << std::endl << "Create table command looks valid";
	std::cout << std::endl << "Table name: " << tokens[2];
	std::cout << std::endl << "Number of columns: " << n_columns;

	for (int i = 0; i < n_tokens; i++) {
		delete[] tokens[i];
	}
	delete[] tokens;

	return true;
}

bool CommandParser::validateCreateIndex() {

	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);

	if (n_tokens < 6) {

		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
		return false;
	}

	if (strcmp(tokens[0], "CREATE") != 0 || strcmp(tokens[1], "INDEX") != 0) {

		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
		return false;
	}

	char* index_name = tokens[2];
	if (strcmp(index_name, "ON") == 0) {

		std::cout << std::endl << "Error: Missing index name";
		return false;
	}

	if (strcmp(tokens[3], "ON") != 0) {

		std::cout << std::endl << "Error: Invalid CREATE INDEX syntax";
		return false;
	}

	char* table_name = tokens[4];
	if (strchr(table_name, '(') != nullptr || strchr(table_name, ')') != nullptr) {

		std::cout << std::endl << "Error: Missing table name";
		return false;
	}

	char* column = tokens[5];
	if (strchr(column, '(') == 0 || strchr(column, ')') == nullptr) {

		std::cout << std::endl << "Error: Missing paranthesis";
		return false;
	}

	std::cout << std::endl << "Create index command looks valid";
	std::cout << std::endl << "Index name: " << index_name;
	std::cout << std::endl << "Table name: " << table_name;
	std::cout << std::endl << "Column name: " << column;

	for (int i = 0; i < n_tokens; i++) {
		delete[] tokens[i];
	}
	delete[] tokens;

	return true;


}

bool CommandParser::validateDropTable() {
	
	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);

	if (n_tokens < 3) {

		std::cout << std::endl << "Error: Invalid DROP TABLE syntax";
		return false;
	}

	if (strcmp(tokens[0], "DROP") != 0 || strcmp(tokens[1], "TABLE") != 0) {

		std::cout << std::endl << "Error: Invalid DROP TABLE syntax";
		return false;
	}

	char* table_name = tokens[2];
	if (strlen(table_name) == 0 || strchr(table_name, '(') != nullptr || strchr(table_name, ')') != nullptr) {

		std::cout << std::endl << "Error: Invalid or missing table name";
		return false;
	}

	std::cout << std::endl << "DROP TABLE command looks valid";
	std::cout << std::endl << "Table name: " << table_name;

	for (int i = 0; i < n_tokens; i++)
		delete[] tokens[i];
	delete[] tokens;

	return true;
}

bool CommandParser::validateDropIndex() {

	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);

	if (n_tokens < 3) {
		std::cout << std::endl << "Error: Invalid DROP INDEX syntax";
		return false;
	}

	if (strcmp(tokens[0], "DROP") != 0 || strcmp(tokens[1], "INDEX") != 0) {
		std::cout << std::endl << "Error: Invalid DROP INDEX syntax";
		return false;
	}

	char* index_name = tokens[2];
	if (strlen(index_name) == 0 || strchr(index_name, '(') != nullptr || strchr(index_name, ')') != nullptr) {
		std::cout << std::endl << "Error: Invalid or missing index name";
		return false;
	}

	std::cout << std::endl << "DROP INDEX command looks valid";
	std::cout << std::endl << "Index name: " << index_name;

	for (int i = 0; i < n_tokens; i++)
		delete[] tokens[i];
	delete[] tokens;

	return true;
}

bool CommandParser::validateDisplayTable() {

	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);

	if (n_tokens < 3) {
		std::cout << std::endl << "Error: Invalid DISPLAY TABLE syntax";
		return false;
	}

	if (strcmp(tokens[0], "DISPLAY") != 0 || strcmp(tokens[1], "TABLE") != 0) {
		std::cout << std::endl << "Error: Invalid DISPLAY TABLE syntax";
		return false;
	}

	char* table_name = tokens[2];
	if (strlen(table_name) == 0 ||
		strchr(table_name, '(') != nullptr ||
		strchr(table_name, ')') != nullptr ||
		strchr(table_name, ',') != nullptr) {

		std::cout << std::endl << "Error: Invalid or missing table name";
		return false;
	}

	std::cout << std::endl << "DISPLAY TABLE command looks valid";
	std::cout << std::endl << "Table name: " << table_name;

	for (int i = 0; i < n_tokens; i++)
		delete[] tokens[i];
	delete[] tokens;

	return true;
}
bool CommandParser::validateInsert()
{
	std::string copy = this->command;
	int n_tokens = 0;
	char** tokens = tokenizeCommand(n_tokens);
	if (n_tokens < 4)
	{
		std::cout << "Error: Invalid INSERT syntax.\n";
		return false;
	}

	if (strcmp(tokens[0], "INSERT") != 0 || strcmp(tokens[1], "INTO") != 0)
	{
		std::cout << "Error: Invalid INSERT syntax.\n";
	}

	char* table_name = tokens[2];
	if (strlen(table_name) == 0 ||
		strchr(table_name, '(') != nullptr ||
		strchr(table_name, ')') != nullptr ||
		strchr(table_name, ',') != nullptr) {

		std::cout << std::endl << "Error: Invalid or missing table name";
		return false;
	}

	if (strcmp(tokens[3], "VALUES") != 0)
	{
		std::cout << std::endl << "Error: Invalid INSERT syntax.";
		return false;
	}

	if (strchr(tokens[4], '(') == nullptr || strchr(tokens[n_tokens - 1], ')') == nullptr) {

		std::cout << std::endl << "Error: Missing paranthesis";
		return false;
	}

	if (strcmp(tokens[4], "(,") == 0) {

		std::cout << std::endl << "Error: Invalid INSERT syntax.";
		return false;
	}

	int n_values = 0;
	for (int i = 4; i < n_tokens - 1; i = i + 1) {

		n_values++;
		if (strcmp(tokens[i], ",") == 0) {

			std::cout << std::endl << "Error: Invalid INSERT syntax.";
			return false;
		}
		if (strchr(tokens[i], ',') == nullptr) {
			std::cout << std::endl << "Error: Expected comma";
			return false;
		}
	}

	if (strchr(tokens[n_tokens - 1], ',') != nullptr) {
		std::cout << std::endl << "Error: Unxpected comma";
		return false;
	}
	else
		n_values++;

	for (int i = 0; i < n_tokens; i++)
	{
		delete[] tokens[i];
	}
	delete[] tokens;

	std::cout << std::endl << "Command INSERT looks valid";
	std::cout << std::endl << "Number of values: " << n_values;
	return true;

}

bool CommandParser::validateDeleteTable() {

	std::string copy = this->command;
	std::regex deleteTableRegex(R"(^\s*DELETE\s+FROM\s+[A-Za-z_][A-Za-z0-9_]*\s+WHERE\s+\w+\s+=\s+\w+$)");
	
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

	std::regex selectRegex(R"(^\s*SELECT\s+(\*|[A-Za-z_][A-Za-z0-9_]*(\s*,\s*[A-Za-z_][A-Za-z0-9_]*)*)\s+FROM\s+[A-Za-z_][A-Za-z0-9_]*(?:\s+WHERE\s+\w+\s+=\s+\w+)?\s*$)");

	if (std::regex_match(this->command, selectRegex)) {

		std::cout << std::endl << "SELECT command looks valid";
		return true;
	}
	else {
		std::cout << std::endl << "Invalid SELECT syntax";
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
		

		default:
			std::cout << std::endl << "Error: Unknown or unsupported command";
			return false;
	}

}
