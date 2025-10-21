#pragma once
#include <cstring>
#include "DataTypes.h"

DataType getDataFromString(char* string_type) {

	int comma_pos = strlen(string_type) - 1;
	string_type[comma_pos] = '\0';

	if (strcmp(string_type, "INTEGER") == 0)
		return INTEGER;
	if (strcmp(string_type, "TEXT") == 0)
		return TEXT;
	if (strcmp(string_type, "DATE") == 0)
		return DATE;
	if (strcmp(string_type, "REAL") == 0)
		return REAL;
	if (strcmp(string_type, "BOOLEAN") == 0)
		return BOOLEAN;
	if (strcmp(string_type, "BLOB") == 0)
		return BLOB;
	return UNKNOWN_DATA_TYPE;
}
