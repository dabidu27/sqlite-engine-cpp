#include "StringUtils.h"
#include <regex>


void StringUtils::toUpper(std::string& command) {

	for (int i = 0; i < command.length(); i++)
		if (command[i] >= 'a' && command[i] <= 'z')
			command[i] = command[i] - 32;
}

void StringUtils::trimString(std::string& s) {
	s = std::regex_replace(s, std::regex("^\\s+|\\s+$"), "");
}