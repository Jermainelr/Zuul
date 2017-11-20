 // A "Room" represents one location in the scenery of the game.  It is 
 // connected to other rooms via exits.  For each existing exit, the room 
 // stores a reference to the neighboring room.
 
#include "Room.h"

using namespace std;

Room::Room(string* newDescription) {
	description = newDescription;
}

Room::~Room() {
	delete description;
}

string* Room::getDescription() {
	return description;
}

void Room::printLongDescription() {
	cout << "You are currently " << *description << endl;
	cout << "There are exits" << endl;
	for(map<string, Room*>::iterator it = exits.begin() ; it != exits.end(); ++it) {
		cout << it->first << " ";
	}
	cout << endl;
	
	if (items.size() == 0) {
		cout << "There are no items in the room." << endl;
	} else {
		for(vector<Item*>::iterator it = items.begin() ; it != items.end(); ++it) {
			cout << "There is a " << *((*it)->getName()) << endl;
		}
	}
}	

void Room::setExit(string* direction, Room* neighbor) {
	exits[*direction] = neighbor;
}

Room* Room::getExit(string* direction) {
	return exits[*direction];
}

void Room::addItem(Item* item) {
	items.push_back(item);
}

Item* Room::getItem(string* name) {
	for(vector<Item*>::iterator it = items.begin() ; it != items.end(); ++it) {
		if(*name == *((*it)->getName())) {
			return *it;
		}
	}
	return NULL;
}

void Room::removeItem(string* name) {
	for(vector<Item*>::iterator it = items.begin() ; it != items.end(); ++it) {
		if(*name == *((*it)->getName())) {
			items.erase(it);
			return;
		}
	}
}