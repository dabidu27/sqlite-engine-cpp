#pragma once
#include <string>
#include "DataTypes.h"


class Columns {

	std::string name = "";
	DataType type;
	int size = 0;
	std::string defaultValue = "";


	public:

		static const int NAME_MIN_SIZE;

		void setName(std::string name);
		void setType(std::string type_string);
		void setSize(int size);
		void setDefaultValue(std::string defaultValue);


		std::string getName();
		DataType getType();
		int getSize();
		std::string getDefaultValue();

		Columns();
		Columns(std::string name, std::string type_string, int size, std::string defaultValue);
		Columns(const Columns& other);
		Columns& operator=(const Columns& other);

		// main output stream testgi
		friend std::ostream& operator<<(std::ostream& os, const Columns& col);
};