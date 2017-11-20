#include "Item.h"

using namespace std;

Item::Item(string* newName) {
	name = newName;
}

Item::~Item() {
	delete name;
}

string* Item::getName() {
	return name;
}


