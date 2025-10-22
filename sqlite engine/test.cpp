#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"

int main() {

	CommandParser parser;
	CommandType type;
	string command = "  CREATE INDEX idx_artist ON albums artist";

	type = parser.recognizeCommand(command);
	cout << endl << "Command type: " << type;
	cout << endl;

	int n_tokens = 0;
	char** command_tokens = parser.tokenizeCommand(command, n_tokens);
	for (int i = 0; i < n_tokens; i++)
		cout << endl << "Token " << i << ": " << command_tokens[i];

	bool valid = parser.validateCommand(command);

	return 0;
	
}