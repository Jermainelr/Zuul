// Room Header File

#include <iostream>
#include <map>
#include <vector>
#include <string.h>
#include "Item.h"

using namespace std;

class Room {
public:
	Room(string* newDescription);	
	virtual ~Room();
	string* getDescription();
	void printLongDescription();
	void setExit(string* direction, Room* neighbor);
	Room* getExit(string* direction);
	void addItem(Item* item);
	Item* getItem(string* name);
	void removeItem(string* name);
	
private:
	string* description;
	vector<Item*> items;
	map<string, Room*> exits;
};

