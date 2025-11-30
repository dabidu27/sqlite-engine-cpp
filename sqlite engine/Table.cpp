#pragma once
#include "Columns.h"
#include "Table.h"




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

Table::Table(std::string* tokens, int n_tokens) {

	this->setTableName(tokens);
	this->setColumns(tokens, n_tokens);
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

Table::~Table() {

	if (this->columns != nullptr) {
		delete[] this->columns;
		this->columns = nullptr;
	}
}