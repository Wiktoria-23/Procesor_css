#include "Attribute.h"

Attribute::Attribute() {
	key = new MyString();
	value = new MyString();
}
MyString& Attribute::getKey() {
	return *key;
}
MyString& Attribute::getValue() {
	return *value;
}
Attribute::~Attribute() {
	if (key != nullptr) {
		delete key;
	}
	if (value != nullptr) {
		delete value;
	}
}