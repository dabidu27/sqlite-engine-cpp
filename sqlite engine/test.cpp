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
	//test
	//if we try to open a binary file in read mode and it doesn t exist => error, so we can check if it exists or not
	ifstream readFile("table_metadata.bin", ios::binary);
	if (readFile.is_open()) { //if the table_metadata file exists (db data is saved)
		db.readTablesMetadata(readFile); //read it and set it to the db object, meaning loading the database
		cout << endl << "Database loaded";
		readFile.close();
	}
	else { //if the file does not exist
		cout << endl << "Empty Database"; //use the default db object (empty)
	}

	// Process default command files and persist metadata if any were processed
	const std::string metadataFilename = "table_metadata.bin";
	bool processedFiles = CommandParser::processDefaultCommandFiles(db);
    if (processedFiles) {
        // Persist metadata after processing files
        ofstream writeFile(metadataFilename.c_str(), ios::binary);
        if (writeFile.is_open()) {
            try {
                db.writeTablesMetadata(writeFile);
                cout << "\nWrote metadata to " << metadataFilename << "\n";
            } catch (const std::exception& e) {
                cerr << "\nError writing metadata: " << e.what() << "\n";
            } catch (const char* s) {
                cerr << "\nError writing metadata: " << s << "\n";
            } catch (...) {
                cerr << "\nUnknown error while writing metadata\n";
            }
            writeFile.close();
        } else {
            cerr << "\nCouldn't create/open metadata file for writing\n";
        }
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

	//save db object state in a binary file
	ofstream writeFile("table_metadata.bin", ios::binary);
	if (writeFile.is_open()) {
		db.writeTablesMetadata(writeFile);
		writeFile.close();
	}
	else {
		throw "Couldn't create/open file";
	}

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