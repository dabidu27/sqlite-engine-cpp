#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"

int main() {

	CommandParser parser;
	CommandType type;
	string command = "   create table album(name text, artist text)";

	type = parser.parseCommand(command);
	cout << endl << "Command type: " << type;

	return 0;
}