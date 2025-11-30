#pragma once
#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"
#include "Table.h"
#include "Database.h";

int main() {

	Database db;

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
				db.addTable(table);
				break;
			}

			default:
	
				cout << endl << "Command not suported yet";
				break;
		}

	}

	delete[] tokens;
	
	command = "CREATE TABLE students2 IF NOT EXISTS ((index, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

	parser = CommandParser(command);
	n_tokens = 0;
	parser.tokenizeCommand();
	tokens = parser.getTokens();
	n_tokens = parser.getNoTokens();

	valid = parser.validateCommand();

	cout << endl;

	if (valid) {

		switch (type) {

		case CREATE_TABLE_CMD:
		{
			Table table = Table(tokens, n_tokens);
			db.addTable(table);
			break;
		}

		default:

			cout << endl << "Command not suported yet";
			break;
		}

	}
	delete[] tokens;

	cout << db;

	return 0;
}