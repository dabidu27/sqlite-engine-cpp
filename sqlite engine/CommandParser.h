#pragma once
#include "CommandType.h"
#include <string>


class CommandParser {
	public:
		CommandType parseCommand(std::string command);

};