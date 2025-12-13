#include "Database.h"
#include <iostream>

Database::Database() {
	this->tables = nullptr;
	this->noTables = 0;
	std::cout << std::endl << "Database created";
}

void Database::addTable(Table table) {

	Table* copy = new Table[this->noTables + 1];
	for (int i = 0; i < this->noTables; i++)
		copy[i] = this->tables[i];

	copy[this->noTables] = table;

	if (this->tables != nullptr) {
		delete[] this->tables;
		this->tables = nullptr;
	}

	this->tables = copy;
	this->noTables++;

}
Table* Database::getTables() {

	Table* copy = new Table[this->noTables];
	for (int i = 0; i < this->noTables; i++)
		copy[i] = this->tables[i];
	return copy;

}

int Database::getNoTables() {

	return this->noTables;
}

void Database::deleteTable(std::string tableName) {

	if (this->noTables == 0)
		throw "No tables to delete";
	int ok = 0;
	for (int i = 0; i < this->noTables; i++)
		if (this->tables[i].getTableName() == tableName)
			ok = 1;
	if (ok == 0)
		throw "Table not found";
	Table* copy = new Table[this->noTables - 1];
	int j = 0;
	for (int i = 0; i < this->noTables; i++)
		if (this->tables[i].getTableName() != tableName)
		{
			copy[j] = this->tables[i];
			j++;
		}

	if (this->tables != nullptr) {
		delete[] this->tables;
		this->tables = nullptr;
	}

	this->tables = copy;
	this->noTables--;

}

Database::~Database() {

	if (this->tables != nullptr) {

		delete[] this->tables;
		this->tables = nullptr;
	}
}

void operator<< (std::ostream& console, Database& db) {

	Table* tables = db.getTables();
	for (int i = 0; i < db.getNoTables(); i++) {
		console << std::endl << tables[i].getTableName() << " " << tables[i].getNoColumns() << std::endl;
		Columns* columns = tables[i].getColumns();
		for (int j = 0; j < tables[i].getNoColumns(); j++)
		{
			console << columns[j] << std::endl;
			console << std::endl;
		}
		delete[] columns;
	}
}

bool Database::operator==(const Database& other) {

	if (this->noTables != other.noTables)
		return false;
	for (int i = 0; i < this->noTables; i++)
		if (this->tables[i] != other.tables[i])
			return false;
	return true;
}

Database::operator int() {

	return this->noTables;
}

void Database::writeTablesMetadata(std::ofstream& file) {

	if (this->tables != nullptr) {

		int noTables = this->noTables;
		file.write((char*)&noTables, sizeof(int));
		for (int i = 0; i < this->noTables; i++)
		{
			
			std::string tableName = this->tables[i].getTableName();
			//write name length
			int tableNameSize = tableName.size();
			file.write((char*)&tableNameSize, sizeof(int));
			//write string
			file.write(tableName.c_str(), tableNameSize);

			//write no. of columns
			int noColumns = this->tables[i].getNoColumns();
			file.write((char*)&noColumns, sizeof(int));

			//write serialized columns
			Columns* columns = this->tables[i].getColumns();
			for (int j = 0; j < noColumns; j++) {

				std::string colName = columns[j].getName();
				int colNameSize = colName.size();
				file.write((char*)&colNameSize, sizeof(int));
				file.write(colName.c_str(), colNameSize);

				DataType colType = columns[j].getType();
				file.write((char*)&colType, sizeof(DataType));

				int colSize = columns[j].getSize();
				file.write((char*)&colSize, sizeof(int));

				std::string colDefault = columns[j].getDefaultValue();
				int colDefaultSize = colDefault.size();
				file.write((char*)&colDefaultSize, sizeof(int));
				file.write(colDefault.c_str(), colDefaultSize);
			}
			delete[] columns;
			columns = nullptr;
		}
	}
}

void Database::readTablesMetadata(std::ifstream& file) {

	file.read((char*)&this->noTables, sizeof(int));
	if (this->tables != nullptr) {
		delete[] this->tables;
		this->tables = nullptr;
	}

	this->tables = new Table[this->noTables];
	for (int i = 0; i < this->noTables; i++) {

		int tableNameSize = 0;
		file.read((char*)&tableNameSize, sizeof(int));
		char* tableNameBuffer = new char[tableNameSize + 1];
		file.read(tableNameBuffer, tableNameSize);
		tableNameBuffer[tableNameSize] = '\0';
		std::string tableName(tableNameBuffer);
		delete[] tableNameBuffer;
		tableNameBuffer = nullptr;
		this->tables[i].setTableNameString(tableName);

		int noColumns = 0;
		file.read((char*)&noColumns, sizeof(int));
		Columns* columns = new Columns[noColumns];
		for (int j = 0; j < noColumns; j++) {

			int colNameSize = 0;
			file.read((char*)&colNameSize, sizeof(int));
			char* colNameBuffer = new char[colNameSize + 1];
			file.read(colNameBuffer, colNameSize);
			colNameBuffer[colNameSize] = '\0';
			std::string colName(colNameBuffer);
			delete[] colNameBuffer;
			colNameBuffer = nullptr;
			columns[j].setName(colName);

			DataType type;
			file.read((char*)&type, sizeof(DataType));
			columns[j].setTypeFromType(type);

			int size = 0;
			file.read((char*)&size, sizeof(int));
			columns[j].setSize(size);

			int colDefaultSize = 0;
			file.read((char*)&colDefaultSize, sizeof(int));
			char* colDefaultBuffer = new char[colDefaultSize + 1];
			file.read(colDefaultBuffer, colDefaultSize);
			colDefaultBuffer[colDefaultSize] = '\0';
			std::string colDefault(colDefaultBuffer);
			delete[] colDefaultBuffer;
			colDefaultBuffer = nullptr;
			columns[j].setDefaultValue(colDefault);
		}
		this->tables[i].setColumnsObjects(columns, noColumns);
		delete[] columns;
		columns = nullptr;
	}
}

void Database::printReadTablesMetadata(std::ifstream& file) {

	int noTables = 0;
	file.read((char*)&noTables, sizeof(int));

	std::cout << "\n========================================" << std::endl;
	std::cout << "  DATABASE METADATA READOUT (TEST MODE)" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "Total Tables Found: " << noTables << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	for (int i = 0; i < noTables; i++) {

		int tableNameSize = 0;
		file.read((char*)&tableNameSize, sizeof(int));
		char* tableNameBuffer = new char[tableNameSize + 1];
		file.read(tableNameBuffer, tableNameSize);
		tableNameBuffer[tableNameSize] = '\0';
		std::string tableName(tableNameBuffer);
		delete[] tableNameBuffer;
		tableNameBuffer = nullptr;

		std::cout << "\nTABLE " << i + 1 << " - Name: " << tableName << std::endl;

		int noColumns = 0;
		file.read((char*)&noColumns, sizeof(int));

		std::cout << "  Columns Found: " << noColumns << std::endl;
		std::cout << "  ------------------------------------" << std::endl;

		for (int j = 0; j < noColumns; j++) {

			int colNameSize = 0;
			file.read((char*)&colNameSize, sizeof(int));
			char* colNameBuffer = new char[colNameSize + 1];
			file.read(colNameBuffer, colNameSize);
			colNameBuffer[colNameSize] = '\0';
			std::string colName(colNameBuffer);
			delete[] colNameBuffer;
			colNameBuffer = nullptr;

			DataType type;
			file.read((char*)&type, sizeof(DataType));

			int size = 0;
			file.read((char*)&size, sizeof(int));

			int colDefaultSize = 0;
			file.read((char*)&colDefaultSize, sizeof(int));
			char* colDefaultBuffer = new char[colDefaultSize + 1];
			file.read(colDefaultBuffer, colDefaultSize);
			colDefaultBuffer[colDefaultSize] = '\0';
			std::string colDefault(colDefaultBuffer);
			delete[] colDefaultBuffer;
			colDefaultBuffer = nullptr;

			std::cout << "  Col " << j + 1 << ": Name=[" << colName
				<< "], Type=[" << int(type)
				<< "], Size=[" << size
				<< "], Default=[" << colDefault << "]" << std::endl;
		}

	}
	std::cout << "\n========================================" << std::endl;
	std::cout << "  READOUT COMPLETE" << std::endl;
	std::cout << "========================================\n" << std::endl;
}

void Database::displayTable(std::string tableName) {

	int found = 0;
	int table_index = 0;
	for (int i = 0; i < this->noTables; i++)
		if (this->tables[i].getTableName() == tableName)
		{
			found = 1;
			table_index = i;
		}
	if (found == 0)
		std::cout << std::endl << "Table not found";
	else {

		std::cout << std::endl;
		std::cout << this->tables[table_index];
		std::cout << std::endl;
	}
}


void Database::createTableFile(std::string tableName) {

	std::string fileName = tableName + ".bin";
	std::ofstream createFile(fileName, std::ios::binary);
	if (createFile.is_open()) {
		createFile.close();
	}
	else {
		throw "Couldn't create file";
	}
}

void Database::deleteTableFile(std::string tableName) {
	
	std::string fileName = tableName + ".bin";
	int status = remove(fileName.c_str());
	if (status != 0) {
		std::cout << std::endl << "Error removing file";
	}
}

void Database::addRowAtIndex(int index, Row row) {

	this->tables[index].addRow(row);
}

void Database::deleteRowAtIndex(int index, int columnNumber, std::string rightArg) {
	
	this->tables[index].deleteRow(columnNumber, rightArg);
}