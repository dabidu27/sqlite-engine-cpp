#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"

int main() {

	string command = "UPDATE users SET age = '25' WHERE id = 1";
	CommandParser parser(command);
	CommandType type;

	type = parser.recognizeCommand();
	cout << endl << "Command type: " << type;
	cout << endl;

	int n_tokens = 0;
	char** command_tokens = parser.tokenizeCommand(n_tokens);
	for (int i = 0; i < n_tokens; i++)
		cout << endl << "Token " << i << ": " << command_tokens[i];

	bool valid = parser.validateCommand();

	return 0;
	
}