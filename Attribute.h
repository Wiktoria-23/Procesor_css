#pragma once
#include "MyString.h"
class Attribute {
private:
	MyString* key;
	MyString* value;
public:
	Attribute();
	MyString& getKey();
	MyString& getValue();
	~Attribute();
 };