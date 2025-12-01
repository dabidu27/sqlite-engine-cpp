
#include <iostream>
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"
#include "Table.h"
#include "Database.h"
using namespace std;

int main() {

	Database db;

	string command = "";
	CommandParser parser = CommandParser("");
	while (true) {

		cout << endl << "Enter command (Exit to stop): ";
		getline(cin, command);

		if (command == "Exit")
			break;

		parser = CommandParser(command);
		parser.runCommand(db);
		cout << endl << "Now DB looks like this: " << endl;
		cout << db;
	}

	return 0;
}