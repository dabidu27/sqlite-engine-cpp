#include <iostream>
using namespace std;
#include "CommandParser.h"
#include "CommandType.h"

int main() {

	string command = "CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

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

	delete[] tokens;
	bool valid = parser.validateCommand();

	return 0;
	
}