#include "StringUtils.h"


void toUpper(std::string& command) {

	for (int i = 0; i < command.length(); i++)
		if (command[i] >= 'a' && command[i] <= 'z')
			command[i] = command[i] - 32;
}
