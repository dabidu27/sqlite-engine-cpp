#pragma once
#include "Columns.h"
#include <fstream>
#include "Row.h"

class Table {
private:
		std::string tableName = "";
		Columns* columns = nullptr;
		int n_columns = 0;
		Row* rows = nullptr;
		int noRows = 0;
public:

	Table();
	Table(std::string* tokens, int n_tokens);
	Table(const Table& other);
	Table& operator=(const Table& other);

	void setTableName(std::string* tokens);
	void setColumns(std::string* tokens, int n_tokens);
	void setColumnsObjects(Columns* columns, int noColumns);
	void setTableNameString(std::string name);

	std::string getTableName();
	int getNoColumns();
	Columns* getColumns();
	Row* getRows();
	int getNoRows();

	void addRow(Row row);
	void deleteRow(int columnNumber, std::string leftArg);


	~Table();

	bool operator==(const Table& other);
	bool operator!= (const Table& other);

	explicit operator std::string();

};

void operator<<(std::ostream& console, Table& table);