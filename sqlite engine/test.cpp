#pragma once
#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"
#include "Table.h"

int main() {

	//TEST COMMAND VALIDATION
	string command = "CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

	CommandParser parser(command);
	CommandType type;

	type = parser.recognizeCommand();

	//get tokens
	int n_tokens = 0;
	parser.tokenizeCommand();
	string* tokens = parser.getTokens();
	n_tokens = parser.getNoTokens();

	//see tokens - optional
	for (int i = 0; i < n_tokens; i++)
		cout << endl << "Token " << i << ": " << tokens[i];

	//validate comand syntax
	bool valid = parser.validateCommand();

	cout << endl;

	//Create table command to columns pipeline
	
	if (valid) {

		switch (type) {

			case CREATE_TABLE_CMD:
			{
				Table table = Table(tokens, n_tokens);
				cout << endl << table.getTableName() << " " << table.getNoColumns() << endl;
				Columns* columns = table.getColumns();
				for (int i = 0; i < table.getNoColumns(); i++)
				{
					//cout << columns[i].getName() << " " << columns[i].getType() << " " << columns[i].getSize() << " " << columns[i].getDefaultValue();
					cout << columns[i] << endl;
					cout << endl;
				}

				delete[] columns;
				break;
			}

			default:
	
				cout << endl << "Command not suported yet";
				break;
		}

	}
	return 0;
}