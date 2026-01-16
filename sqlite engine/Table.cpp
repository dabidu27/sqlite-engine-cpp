#include "Columns.h"
#include "Table.h"
#include <iostream>
#include <iomanip>


void Table::setTableName(std::string* tokens) {

	this->tableName = tokens[2];
}


void Table::setColumns(std::string* tokens, int n_tokens) {

	Columns* copy = new Columns[100];
	this->n_columns = 0;

	std::string* values = new std::string[4];
	int j = 0;

	int i = 3;
	if (tokens[i] == "IF")
		i = 6;
	while (i < n_tokens) {

		if (tokens[i] == "(" && tokens[i + 1] == "(") {
			i = i + 2;
			continue;
		}
		while (tokens[i] != ")") {

			if (tokens[i] != "," && tokens[i] != "'" && tokens[i] != "(" && j < 4)
			{
				values[j] = tokens[i];
				j++;
			}
			if (tokens[i] == "'" && tokens[i + 1] == "'" && j < 4)
			{
				values[j] = "";
				j++;

			}
			i++;
		}

		if (tokens[i] == ")")
		{

			if (j > 0)
			{
				std::string column_name = values[0];
				std::string data_type = values[1];
				int size = stoi(values[2]);
				std::string default_value = values[3];
				copy[this->n_columns] = Columns(column_name, data_type, size, default_value);
				this->n_columns++;
			}

			delete[] values;
			values = new std::string[4];
			j = 0;
			i++;
			continue;
		}
	}

	if (values != nullptr)
	{
		delete[] values;
		values = nullptr;
	}

	this->columns = new Columns[this->n_columns];
	for (int i = 0; i < this->n_columns; i++)
		this->columns[i] = copy[i];
	delete[] copy;
}

Table::Table() {

	this->tableName = "";
	this->n_columns = 0;
	this->columns = nullptr;
	this->noRows = 0;
	this->rows = nullptr;
}

Table::Table(std::string* tokens, int n_tokens) {

	this->setTableName(tokens);
	this->setColumns(tokens, n_tokens);
	std::cout << std::endl << "Table Created";
}

Table::Table(const Table& other)
{
	this->tableName = other.tableName;
	this->n_columns = other.n_columns;
	this->noRows = other.noRows;

	if (other.columns != nullptr) 
	{
		this->columns = new Columns[this->n_columns];
		for (int i = 0; i < this->n_columns; i++)
			this->columns[i] = other.columns[i];
	}
	else this->columns = nullptr;

	if (other.rows != nullptr) {

		this->rows = new Row[this->noRows];
		for (int i = 0; i < this->noRows; i++)
			this->rows[i] = other.rows[i];
	}
	else this->rows = nullptr;
}

Table& Table::operator=(const Table& other) {
	
	if (this == &other) {
		return *this;
	}

	if (this->columns != nullptr) {
		delete[] this->columns;
		this->columns = nullptr;
	}

	if (this->rows != nullptr) {
		delete[] this->rows;
		this->rows = nullptr;
	}

	
	this->tableName = other.tableName;
	this->n_columns = other.n_columns;
	this->noRows = other.noRows;

	this->columns = new Columns[this->n_columns];
	for (int i = 0; i < this->n_columns; i++) 
		this->columns[i] = other.columns[i];

	this->rows = new Row[this->noRows];
	for (int i = 0; i < this->noRows; i++)
		this->rows[i] = other.rows[i];

	return *this;

}

std::string Table::getTableName() {

	return this->tableName;
}

int Table::getNoColumns() {

	return this->n_columns;
}

Columns* Table::getColumns() {

	Columns* copy = new Columns[this->n_columns];
	for (int i = 0; i < this->n_columns; i++)
		copy[i] = this->columns[i];
	return copy;
}

int Table::getNoRows() {
	return this->noRows;
}

Row* Table::getRows(){

	Row* copy = new Row[this->noRows];
	for (int i = 0; i < this->noRows; i++)
		copy[i] = this->rows[i];
	return copy;
}

Table::~Table() {

	if (this->columns != nullptr) {
		delete[] this->columns;
		this->columns = nullptr;
	}

	if (this->rows != nullptr) {
		delete[] this->rows;
		this->rows = nullptr;
	}
}

bool Table::operator==(const Table& other) {

	if (this->tableName != other.tableName)
		return false;
	if (this->n_columns != other.n_columns)
		return false;
	for (int i = 0; i < this->n_columns; i++)
		if (this->columns[i] != other.columns[i])
			return false;
	return true;
}

bool Table::operator!=(const Table& other) {

	if (this->tableName != other.tableName)
		return true;
	if (this->n_columns != other.n_columns)
		return true;
	for (int i = 0; i < this->n_columns; i++)
		if (this->columns[i] != other.columns[i])
			return true;
	return false;
}

Table::operator std::string() {
	return this->tableName;
}

void operator<<(std::ostream& console, Table& table) {

	int width = 15;

	console << std::endl;
	console << std::endl << "Table name: " << table.getTableName();
	console << std::endl << std::endl << "Columns: ";
	Columns* columns = table.getColumns();
	for (int i = 0; i < table.getNoColumns(); i++)
		console << std::endl << columns[i];

	console << std::endl << std::endl;
	//columns header
	for (int i = 0; i < table.getNoColumns(); i++)
		console << std::setw(width) << columns[i].getName();
	console << std::endl;
	//separator
	for (int i = 0; i < table.getNoColumns(); i++) {
		console << std::setw(width) << std::string(width - 1, '-');
	}
	Row* rows = table.getRows();
	for (int i = 0; i < table.getNoRows(); i++) {
		console << rows[i];
	}
	delete[] columns;
	columns = nullptr;
	delete[] rows;
	rows = nullptr;
}

void Table::setColumnsObjects(Columns* columns, int noColumns) {

	if (this->columns != nullptr) {
		delete[] this->columns;
		this->columns = nullptr;
	}

	this->columns = new Columns[noColumns];
	this->n_columns = noColumns;

	for (int i = 0; i < this->n_columns; i++)
		this->columns[i] = columns[i];
}

void Table::setTableNameString(std::string name) {
	this->tableName = name;
}

void Table::addRow(Row row) {

	Row* copy = new Row[this->noRows + 1];

	for (int i = 0; i < this->noRows; i++)
		copy[i] = this->rows[i];

	copy[this->noRows] = row;

	if (this->rows != nullptr) {
		delete[] this->rows;
		this->rows = nullptr;
	}

	this->rows = copy;
	this->noRows++;
}


void Table::deleteRow(int columnNumber, std::string rightArg) {

	if (this->rows == nullptr || this->noRows == 0)
	{
		std::cout << std::endl << "No rows to delete";
		return;
	}

	Row* copy = new Row[this->noRows];
	int j = 0;
	int foundValue = 0;
	for (int i = 0; i < this->noRows; i++) {
		std::string* values = this->rows[i].getValues();
		if (values[columnNumber] == rightArg)
			foundValue = 1;
		if (values[columnNumber] != rightArg)
		{
			copy[j] = this->rows[i];
			j++;
		}
	}

	if (foundValue == 1) {

		if (this->rows != nullptr) {
			delete[] this->rows;
			this->rows = nullptr;
		}

		this->rows = copy;
		this->noRows = j;
	}
	else
	{
		std::cout << std::endl << "Value not found on column " << this->columns[columnNumber].getName();
		delete[] copy;
		copy = nullptr;
	}
}