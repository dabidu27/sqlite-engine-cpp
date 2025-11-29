#pragma once
#include <string>

enum DataType {
    INTEGER,
    TEXT,
    FLOAT,
    UNKNOWN_DATA_TYPE
};

class DataValidator {

    public:

        static DataType getDataFromString(std::string string_type);
        static bool validateInt(std::string value);
        static bool validateFloat(std::string value);

};
