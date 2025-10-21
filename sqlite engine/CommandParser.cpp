#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "CommandParser.h"
#include "StringUtils.h"
#include <cstring>

CommandType CommandParser::recognizeCommand(std::string command) {
	
	toUpper(command);
	
	//remove blank spaces at the beggining of the command if they exist
	while (!command.empty() && command[0] == ' ')
		command.erase(0, 1); //erases one character starting from position 0

	//.find() returns the position at which a substring begins
	if (command.find("CREATE TABLE") == 0)
		return CREATE_TABLE_CMD;
	else if (command.find("CREATE INDEX") == 0)
		return CREATE_INDEX_CMD;
	else if (command.find("DROP TABLE") == 0)
		return DROP_TABLE_CMD;
	else if (command.find("DROP INDEX") == 0)
		return DROP_INDEX_CMD;
	else if (command.find("DISPLAY TABLE") == 0)
		return DISPLAY_TABLE_CMD;
	else if (command.find("INSERT") == 0)
		return INSERT_CMD;
	else if (command.find("SELECT") == 0)
		return SELECT_CMD;
	else if (command.find("UPDATE") == 0)
		return UPDATE_CMD;
	else if (command.find("DELETE") == 0)
		return DELETE_CMD;
	else
		return UNKNOWN;
}

char** CommandParser::tokenizeCommand(std::string command, int& n_tokens) {

	char* copy = new char[command.length() + 1];
	strcpy(copy, command.c_str());

	char* token = strtok(copy, " ");
	while (token){
		
		n_tokens++;
		token = strtok(nullptr, " ");
	}

	char** tokens = new char* [n_tokens];

	strcpy(copy, command.c_str());
	token = strtok(copy, " ");
	int i = 0;
	while (token && i < n_tokens) {
		
		tokens[i] = new char[strlen(token) + 1];
		strcpy(tokens[i], token);
		token = strtok(nullptr, " ");
		i++;
	}
	
	delete[] copy;
	return tokens;
}