// Header file for Items
#pragma once

#include <iostream>
#include <string.h>

using namespace std;
	

class Item {
public:
	Item(string* newName);	
	virtual ~Item();
	string* getName();
	
private:
	string* name;
};

