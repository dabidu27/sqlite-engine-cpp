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

void BinaryFilesManager::writeTableRows(std::string tableName, Database& db) {

	std::string fileName = tableName + ".bin";
	Table* tables = db.getTables();
	for(int i = 0; i < db.getNoTables(); i++)
		if (tables[i].getTableName() == tableName) {

			std::ofstream writeFile(fileName, std::ios::binary);
			if (writeFile.is_open()) {

				//write no of rows
				int noRows = tables[i].getNoRows();
				writeFile.write((char*)&noRows, sizeof(int));

				//write no of values per row - each row should have the same no of values, so write only once
				//the no of values per row is also equal to the no of columns
				int noValues = tables[i].getNoColumns();
				writeFile.write((char*)&noValues, sizeof(int));
				Row* rows = tables[i].getRows();
				for (int j = 0; j < noRows; j++) {

					std::string* values = rows[j].getValues();
					for (int z = 0; z < noValues; z++) {

						//write value(a string) size
						int size = values[z].size();
						writeFile.write((char*)&size, sizeof(int));
						//write value
						writeFile.write(values[z].c_str(), size);
					}
					delete[] values;
					values = nullptr;
				}

				delete[] rows;
				rows = nullptr;

				writeFile.close();
			}
			else {
				throw "Couldn't create/open file";
			}
			break;
		}
}

void BinaryFilesManager::loadTableRows(Database& db) {

	Table* tables = db.getTables();
	for (int i = 0; i < db.getNoTables(); i++) {

		std::string filename = tables[i].getTableName() + ".bin";
		std::ifstream readFile(filename, std::ios::binary);
		if (readFile.is_open()) {

			//check if file is empty or not
			readFile.seekg(0, std::ios::end); //go to file end
			if (readFile.tellg() == 0) //if we are still on 0, it means the file is empty
				continue;
			else { //else, for each table with a non empty file, meaning it had data inserted
				readFile.seekg(0, std::ios::beg); //go back to file beggining
				int noRows; //read noRows
				readFile.read((char*)&noRows, sizeof(int));

				int noValues; //read noValues
				readFile.read((char*)&noValues, sizeof(int));

				for (int j = 0; j < noRows; j++) { //for each row, read the values and add to a values array
					std::string* values = new std::string[noValues];
					for (int z = 0; z < noValues; z++) {
						int valueSize = 0;
						readFile.read((char*)&valueSize, sizeof(int));
						char* valueBuffer = new char[valueSize + 1];
						readFile.read(valueBuffer, valueSize);
						valueBuffer[valueSize] = '\0';
						std::string value(valueBuffer);
						delete[] valueBuffer;
						valueBuffer = nullptr;
						values[z] = value;
					}

					Row row(values, noValues); //create a Row object using the values array
					db.addRowAtIndex(i, row); //add it to the table
					delete[] values;
					values = nullptr;
				}
			}
		}
		else {
			throw "Couldn't open file";
		}
	}
}