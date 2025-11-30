#pragma once
#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"

int main() {

	//TEST COMMAND VALIDATION
	string command = "CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

	CommandParser parser(command);
	CommandType type;

	type = parser.recognizeCommand();
	cout << endl << "Command type: " << type;
	cout << endl;

	//get tokens
	int n_tokens = 0;
	parser.tokenizeCommand();
	string* tokens = parser.getTokens();
	n_tokens = parser.getNoTokens();
	//see tokens
	for (int i = 0; i < n_tokens; i++)
		cout << endl << "Token " << i << ": " << tokens[i];
	//validate comand syntax
	bool valid = parser.validateCommand();

	//Create table command to columns pipeline
	
	if (valid) {

		string* values = new string[4];
		int j = 0;
		string table_name = tokens[2];
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
					string column_name = values[0];
					string data_type = values[1];
					int size = stoi(values[2]);
					string default_value = values[3];
					Columns column = Columns(column_name, data_type, size, default_value);
					cout << endl;
					cout << endl << column.getName() << endl << column.getType() << endl << column.getSize() << endl << column.getDefaultValue();
				}
			
				delete[] values;
				values = new string[4];
				j = 0;
				i++;
				continue;
			}
		}
	}

	return 0;
	
}