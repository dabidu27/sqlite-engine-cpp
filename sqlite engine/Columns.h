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
		void setType(DataType type);
		void setSize(int size);
		void setDefaultValue(std::string defaultValue);


		std::string getName();
		DataType getType();
		int getSize();
		std::string getDefaultValue();

		Columns(std::string name, DataType type, int size, std::string defaultValue);
};