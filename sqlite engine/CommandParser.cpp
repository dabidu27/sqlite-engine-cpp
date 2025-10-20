#pragma once
#include "CommandParser.h"
#include "StringUtils.h"

CommandType CommandParser::parseCommand(std::string command) {
	
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