#pragma once
#include <string>



class Row {

	std::string* values = nullptr;
	int noValues = 0;
	
	public:

		Row();

		void setValues(std::string* values, int noValues);
		std::string* getValues();
		int getNoValues();

		Row(std::string* values, int noValues);

		Row(const Row& other);

		void operator= (const Row& other);
};

void operator<<(std::ostream& console, Row& row);