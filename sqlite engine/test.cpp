#include <fstream>
#include <iostream>
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"
#include "Table.h"
#include "Database.h"
#include "BinaryFilesManager.h"

using namespace std;

int main() {

	Database db;

	BinaryFilesManager::loadMetadata(db);
	BinaryFilesManager::loadTableRows(db);


	// reading from text file
	// Process default command files and persist metadata if any were processed
	bool processedFiles = CommandParser::processDefaultCommandFiles(db);
	if (processedFiles) {
		BinaryFilesManager::writeMetadata(db);
	}

	//run commands => modify db object
	string command = "";
	CommandParser parser = CommandParser("");
	while (true) {

		cout << endl << "Enter command (Exit to stop): ";
		getline(cin, command);

		if (command == "Exit" || command == "exit")
			break;

		parser = CommandParser(command);
		parser.runCommand(db);
		cout << endl << "Now DB looks like this: " << endl;
		cout << db;
	}

	BinaryFilesManager::writeMetadata(db);

	//test to see the contents of the binary file
	ifstream printReadFile("table_metadata.bin", ios::binary);
	if (printReadFile.is_open()) {
		db.printReadTablesMetadata(printReadFile);
		printReadFile.close();
	}
	else {
		throw "Couldn't open file";
	}

	return 0;
}