#pragma once
#include <string>

enum DataType {
    INTEGER,
    TEXT,
    DATE,
    REAL,
    BOOLEAN,
    BLOB,
    UNKNOWN_DATA_TYPE
};

DataType getDataFromString(char* string_type);