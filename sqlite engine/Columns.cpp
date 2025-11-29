#pragma once
#include <string>
#include "Columns.h"
#include <iostream>
#include "DataTypes.h"


const int Columns::NAME_MIN_SIZE = 2;

void Columns::setName(std::string name) {

	if (name.size() < NAME_MIN_SIZE)
		throw "Length for name to small";
	this->name = name;
}

void Columns::setSize(int size) {

	if (size < 0)
		throw "Invalid value for size (negative value)";
	this->size = size;
}

void Columns::setType(DataType type) {

	if (type != INTEGER && type != FLOAT && type != TEXT)
		this->type = UNKNOWN_DATA_TYPE;
	else
		this->type = type;
}

void Columns::setDefaultValue(std::string defaultValue) {

	if (defaultValue.size() > this->size)
		throw "Default value cannot be larger than the column size";
	switch (this->type) {

		case INTEGER:
			
			if (!DataValidator::validateInt(defaultValue))
				throw "Invalid int value";
			this->defaultValue = defaultValue;
			break;
			
		case FLOAT:

			if (!DataValidator::validateFloat(defaultValue))
				throw "Invalid float value";
			this->defaultValue = defaultValue;
			break;

		case TEXT:
			
			this->defaultValue = defaultValue;
			break;

		default:

			throw "Unsupported Data Type";
			break;
	}
}

std::string Columns::getName() {

	return this->name;
}

int Columns::getSize() {
	return this->size;
}

DataType Columns::getType() {
	return this->type;
}

std::string Columns::getDefaultValue() {
	return this->defaultValue;
}


Columns::Columns(std::string name, DataType type, int size, std::string defaultValue) {

	this->setName(name);
	this->setType(type);
	this->setSize(size);
	this->setDefaultValue(defaultValue);
}