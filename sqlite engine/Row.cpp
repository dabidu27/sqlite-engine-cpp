#include "Row.h"
#include <iostream>

Row::Row() {

	this->values = nullptr;
	this->noValues = 0;
}

void Row::setValues(std::string* values, int noValues){

	if (noValues <= 0 || values == nullptr) {
		this->values = nullptr;
		this->noValues = 0;
		return;
	}

	this->values = new std::string[noValues];
	for (int i = 0; i < noValues; i++)
		this->values[i] = values[i];
	this->noValues = noValues;
}

Row::Row(std::string* values, int noValues) {
	this->setValues(values, noValues);
}

Row::Row(const Row& other) {

	this->values = new std::string[other.noValues];
	for (int i = 0; i < other.noValues; i++)
		this->values[i] = other.values[i];
	this->noValues = other.noValues;
}

void Row::operator=(const Row& other) {

	if (this == &other)
		return;

	if (this->values != nullptr) {
		delete[] this->values;
		this->values = nullptr;
	}

	this->values = new std::string[other.noValues];
	for (int i = 0; i < other.noValues; i++)
		this->values[i] = other.values[i];

	this->noValues = other.noValues;
}

int Row::getNoValues() {
	return this->noValues;
}

std::string* Row::getValues() {

	if (this->values == nullptr)
		return nullptr;
	std::string* copy = new std::string[this->noValues];
	for (int i = 0; i < this->noValues; i++)
		copy[i] = this->values[i];
	return copy;
}

void operator<<(std::ostream& console, Row& row) {

	console << std::endl;
	std::string* values = row.getValues();
	for (int i = 0; i < row.getNoValues(); i++)
		console << values[i] << " ";
	delete[] values;
	values = nullptr;
}