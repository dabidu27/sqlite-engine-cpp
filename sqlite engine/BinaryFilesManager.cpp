#include "BinaryFilesManager.h"
#include <fstream>
#include "Database.h"
#include <iostream>

void BinaryFilesManager::loadMetadata(Database& db) {
	
	//if we try to open a binary file in read mode and it doesn t exist => error, so we can check if it exists or not
	std::ifstream readFile("table_metadata.bin", std::ios::binary);
	if (readFile.is_open()) { //if the table_metadata file exists (db data is saved)
		db.readTablesMetadata(readFile); //read it and set it to the db object, meaning loading the database
		std::cout << std::endl << "Database loaded";
		readFile.close();
	}
	else { //if the file does not exist
		std::cout << std::endl << "Empty Database"; //use the default db object (empty)
	}
}

void BinaryFilesManager::writeMetadata(Database& db) {

	//save db object state in a binary file
	std::ofstream writeFile("table_metadata.bin", std::ios::binary);
	if (writeFile.is_open()) {
		db.writeTablesMetadata(writeFile);
		writeFile.close();
	}
	else {
		throw "Couldn't create/open file";
	}
}