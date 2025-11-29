#pragma once
#include <cstring>
#include "DataTypes.h"

DataType DataValidator::getDataFromString(std::string string_type) {


	if (string_type == "INTEGER")
		return INTEGER;
	if (string_type == "TEXT")
		return TEXT;
	if (string_type == "FLOAT")
		return FLOAT;
	return UNKNOWN_DATA_TYPE;
}

bool DataValidator::validateInt(std::string value) {

	int start = 0;
	if (value.size() == 1 && value[0] == '-')
		return false; //only - is not a valid int
	
	if (value.size() > 1 && value[0] == '-')
		start = 1;

	for (int i = start; i < value.size(); i++)

		if (!isdigit(value[i]))
			return false; //only digits are allowed for an int
	return true;
}

bool DataValidator::validateFloat(std::string value) {

	int n_points = 0;
	int start = 0;
	if (value.size() == 1 && value[0] == '.')
		return false; // . is not a float

	if (value.size() == 1 && value[0] == '-')
		return false; //only - is not a float int
	
	if (value.size() > 1 && value[0] == '-')
		start = 1;

	for (int i = start; i < value.size(); i++)

		if (!isdigit(value[i]) && value[i] != '.')
			return false;
		else if (value[i] == '.')
			n_points++;

	if (n_points > 1)
		return false; //1.2.3 is not a valid float

	return true;

}