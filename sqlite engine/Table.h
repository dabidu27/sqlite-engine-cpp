#pragma once
#include "Columns.h"

class Table {
private:
		std::string tableName = "";
		Columns* columns = nullptr;
		int n_columns = 0;
public:

	Table();
	Table(std::string* tokens, int n_tokens);
	Table(const Table& other);
	void operator=(const Table& other);

	void setTableName(std::string* tokens);
	void setColumns(std::string* tokens, int n_tokens);

	std::string getTableName();
	int getNoColumns();
	Columns* getColumns();

	~Table();

	bool operator==(const Table& other);
	bool operator!= (const Table& other);

};