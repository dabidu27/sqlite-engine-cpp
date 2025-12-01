
#include <iostream>
#include "CommandParser.h"
#include "CommandType.h"
#include "Columns.h"
#include "Table.h"
#include "Database.h";
using namespace std;

int main() {

	Database db;

	string command = "CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

	CommandParser parser(command);
	parser.runCommand(db);

	command = "CREATE TABLE students2 IF NOT EXISTS ((index, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))";

	cout << endl;

	parser = CommandParser(command);
	parser.runCommand(db);
	cout << endl << "Now DB looks like this: " << endl;
	cout << db;

	command = "DROP TABLE students2";

	parser = CommandParser(command);
	parser.runCommand(db);
	cout << endl << "Now DB looks like this: " << endl;
	cout << db;

	return 0;
}