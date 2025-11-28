#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"

int main() {

	string command = "UPDATE studenti SET nume = \"Alice\", id = 4 WHERE id = 1";

	CommandParser parser(command);
	CommandType type;

	type = parser.recognizeCommand();
	cout << endl << "Command type: " << type;
	cout << endl;

	int n_tokens = 0;
	parser.tokenizeCommand();
	string* tokens = parser.getTokens();
	n_tokens = parser.getNoTokens();
	for (int i = 0; i < n_tokens; i++)
		cout << endl << "Token " << i << ": " << tokens[i];

	bool valid = parser.validateCommand();

	return 0;
	
}