#include <fstream>
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

	ofstream writeFile("table_metadata.bin", ios::binary);
	if (writeFile.is_open()) {
		db.writeTabelsMetadata(writeFile);
		writeFile.close();
	}
	else {
		throw "Couldn't create/open file";
	}

	ifstream readFile("table_metadata.bin", ios::binary);
	if (readFile.is_open()) {
		db.printReadTablesMetadata(readFile);
		readFile.close();
	}
	else {
		throw "Couldn't open file";
	}

	return 0;
}