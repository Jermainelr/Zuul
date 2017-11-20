/**
 * Program made by Jermaine Lara
 * 11/20/17
 * This is the main function of the "World of Zuul" application.
 * "World of Zuul" is a very simple, text based adventure game. Users can walk
 * around some scenery. That's all. It should really be extended to make it more
 * interesting!
 * 
 * To play this game, create an instance of this class and call the "play"
 * method.
 * 
 * This main function creates and initializes all the others: it creates all rooms,
 * and includes all the logic of the game
 * 
 * Based on Java Program made by: Michael Kolling and David J. Barnes
 * Also based on the Java version that I made for the Java Programming Class
 */
#include <iostream>
#include <map>
#include <vector>
#include <string.h>

#include "Room.h"
#include "Item.h"

bool goRoom(Room** currentRoom, Room* home, vector<Item*> & inventory);
void getItem(Room* currentRoom, vector<Item*> & inventory);
void dropItem(Room* currentRoom, vector<Item*> & inventory);
void printInventory(vector<Item*> & inventory);
void printHelp();

int main () {
	Room *currentRoom, *nextRoom;
	Room *courtyard, *mainEntrance, *busStop, *lab, *lockerRooms, *track,
		*baseballPitches, *footballField, *gym, *library, *quietHallway,
		*clubRoom, *bandRoom, *home, *cafeteria, *parkingLot;
	vector<Item*> inventory;
	
	// create the rooms (all rooms are the same as my java program's rooms)
	courtyard = new Room(
			new string("in the courtyard of your school, nice and breezy weather we're having"));
	mainEntrance = new Room(
			new string("in the main entrance of the school, you can see secrateries and teachers busy at work inside the office"));
	lab = new Room(new string("in a computing lab, students are hard at work coding"));
	// Where you can drop off items that you'll need to complete the game
	busStop = new Room(
			new string("in the bus stop, you should get all your stuff and drop it off here before you go home"));
	// Where you get your gym clothes (an item you need to finish the game)
	lockerRooms = new Room(
			new string("in the stinkiest place in the school. Yuck! Speaking of stinky you should probably take your GymClothes home"));
	track = new Room(
			new string("in your schools track, they're about to start practice soon"));
	// If you get to this room the game ends
	home = new Room(new string("in your home sweet home"));
	// Where you get your helmet (an item you need to finish the game)
	footballField = new Room(
			new string("in the football field, you mustv'e forgot your Helmet after practice yesterday"));
	gym = new Room(
			new string("in the gym, the volleyball girls are already practicing, you should probably leave"));
	quietHallway = new Room(
			new string("in a quiet hallway, feels kinda lonely walking through it"));
	// Where you get your textbook (an item you need to finish the game)
	library = new Room(
			new string("in the library, you should probably grab your TextBook but make sure that you're quiet"));
	clubRoom = new Room(
			new string("in the club room, looks like the cooking club is making something, it smells delicious"));
	// Where you get your brother's drum sticks (an item you need to finish
	// the game)
	bandRoom = new Room(
			new string("in the band room, your brother left his DrumSticks here you should probably bring them to him"));
	parkingLot = new Room(
			new string("in the parking lot, look both ways before you cross the street"));
	// Where you get your lunch box (an item you need to finish the game)
	cafeteria = new Room(
			new string("in the cafeteria, you left your LunchBox here and you should probably get it or you'll have to eat that nasty cafeteria food tomorrow"));

	// initialize room exits
	courtyard->setExit(new string("east"), mainEntrance);
	courtyard->setExit(new string("south"), track);
	courtyard->setExit(new string("west"), lab);
	courtyard->setExit(new string("north"), lockerRooms);

	mainEntrance->setExit(new string("west"), courtyard);
	mainEntrance->setExit(new string("east"), parkingLot);
	mainEntrance->setExit(new string("north"), cafeteria);

	lab->setExit(new string("east"), courtyard);
	lab->setExit(new string("west"), quietHallway);

	quietHallway->setExit(new string("north"), library);
	quietHallway->setExit(new string("west"), clubRoom);
	quietHallway->setExit(new string("east"), lab);

	library->setExit(new string("south"), quietHallway);
	library->addItem(new Item(new string("Textbook")));

	cafeteria->setExit(new string("west"), lockerRooms);
	cafeteria->setExit(new string("south"), mainEntrance);
	cafeteria->addItem(new Item(new string("LunchBox")));

	lockerRooms->setExit(new string("west"), gym);
	lockerRooms->setExit(new string("east"), cafeteria);
	lockerRooms->setExit(new string("south"), courtyard);
	lockerRooms->addItem(new Item(new string("GymClothes")));

	track->setExit(new string("north"), courtyard);
	track->setExit(new string("west"), footballField);

	footballField->setExit(new string("east"), track);
	footballField->addItem(new Item(new string("Helmet")));

	clubRoom->setExit(new string("south"), bandRoom);
	clubRoom->setExit(new string("east"), quietHallway);

	bandRoom->setExit(new string("north"), clubRoom);
	bandRoom->addItem(new Item(new string("DrumSticks")));

	parkingLot->setExit(new string("south"), busStop);
	parkingLot->setExit(new string("west"), mainEntrance);

	busStop->setExit(new string("east"), home);
	busStop->setExit(new string("north"), parkingLot);

	gym->setExit(new string("east"), lockerRooms);

	home->setExit(new string("west"), busStop);

	currentRoom = courtyard; // start game in the courtyard
	
	// Print out the opening message for the player
	cout << "Welcome to Zuul!" << endl;
	cout << "Zuul is a game in which you need to find 5 items and drop them off at the bus to go home." << endl;
	cout << "Type 'help' if you need help." << endl;
	currentRoom->printLongDescription();

	// Enter the main command loop. Here we repeatedly read commands and
	// execute them until the game is over.
	char command[81];
	bool quit = false;
	do {
		cout << ">";
		cin >> command;
		quit = false;
		if (strcmp(command,"go") == 0) {
			quit = goRoom(&currentRoom, home, inventory);
	    }
		else if (strcmp(command, "get") == 0) {
			getItem(currentRoom, inventory);
		}
		else if (strcmp(command, "drop") == 0) {
			dropItem(currentRoom, inventory);
		}
		else if (strcmp(command, "quit") == 0) {
			quit = true;
		}
		else if (strcmp(command, "inventory") == 0) {
			printInventory(inventory);
		}
		else if (strcmp(command, "help") == 0) {
			printHelp();
		}
		else {
			cout << "Invalid Command. Type 'help' for list of valid commands(All commands are lower case)" << endl;
		}
	} while(!quit); 
}

bool goRoom(Room** currentRoom, Room* home, vector<Item*> & inventory) {
	//Prompt User Where
	char direction[81];
	cout << "In what direction?" << endl;
	cin >> direction;
	Room* nextRoom = (*currentRoom)->getExit(new string(direction));
	if (nextRoom == NULL)
		cout << "There is no door!" << endl;
	
	else if (nextRoom == home) {
		// Winning condition
		if (inventory.size() == 5) {
			cout << "You Win!" << endl;
		} else {
			cout << "You Need to get all the 5 Items First!" << endl;
			cout << "You Lose, you forgot to get all the 5 Items First!" << endl;
		}
		return true;
	} else {
		*currentRoom = nextRoom;
		(*currentRoom)->printLongDescription();
	}
	return false;
}

// Function that picks up items
void getItem(Room* currentRoom, vector<Item*> & inventory) {
	cout << "Get What Item?" << endl;
	char name[81];
	cin >> name;
	Item* newItem = currentRoom->getItem(new string(name));

	if (newItem == NULL)
		cout << "That item is not here!" << endl;
	else {
		inventory.push_back(newItem);
		currentRoom->removeItem(new string(name));
		cout << "Picked up:" << name << endl;
	}
}

// Function that drops items
void dropItem(Room* currentRoom, vector<Item*> & inventory) {
	cout << "Drop What Item?" << endl;
	char name[81];
	cin >> name;

	for (vector<Item *>::iterator it = inventory.begin() ; it != inventory.end(); ++it) { 
		if (*((*it)->getName()) == name) {
			currentRoom->addItem(*it);
			inventory.erase(it);
			cout << "Dropped:" << name << endl;
			return;
		}
	}
	cout << "That item is not in your inventory!" << endl;
}

// Function that prints inventory
void printInventory(vector<Item*> & inventory) {
	if(inventory.size() == 0) {
		cout << "You aren't carrying any items" << endl;
	} else {
		cout << "You are carrying the following items:" << endl;
		for (vector<Item *>::iterator it = inventory.begin() ; it != inventory.end(); ++it) {
			cout << *((*it)->getName()) << " ";
		}
		cout << endl;
	}
}

// Function that prints help 
void printHelp() {
	cout << "You are lost. You are alone. You wander around the school." << endl << endl;
	cout << "Your command words are: go, get, drop, inventory (all lowercase)" << endl;
	cout << "NOTE: when using go, get or drop, first type the command word. Afterwards you will be asked for the second argument" << endl;
	}# Zuul
# Zuul
# Zuul
