About the Project:
Using C to design and implement a text adventure game similar to Clue. A user will be able to navigate their avatar through
a virtual game board to solve the murder mystery or who the murderer is, what weapon they used, and what room the murder
happened in.

How to Compile the Project:
1. Use gcc to compile the project.

How to Manage User Input:
1. fgets() 

avatar.c:
1. create_player(): Allocates memory to create an Avatar struct and initializes its fields. Takes in a char* argument, which is the name of the avatar.
2. inventory(): Prints out the avatar's inventory. Takes in the Avatar struct * as an argument from which its inventory will be accessed.
3. take(): Allows the avatar to take an item from the room they're currently in. Takes in a char * argument which is the name of the item they want to take and the struct Avatar * is the avatar doing the taking.
4. drop(): Allows the avatar to drop an item from their inventory and add it into the room they're currently in. Takes in a char * item argument of the item's name they want to drop. Takes in a struct Avatar * argument
   where the inventory will be accessed.
5. look(): Allows the avatar to look at the current room's information. Takes in a struct Avatar * argument whose fields will be accessed. Calls the functions room_items(), room_chars(), and room_dir() to help print the
   current room's items, characters, and surrounding rooms.
6. move_player(): Moves the avatar in the given direction. Takes in a struct Avatar * argument whose fields will be accessed and a char * argument, which is the name of the direction the user wants to go in. Checks if
   the room in the given direction is not NULL and sets the avatar's location to the directional room.

avatar.h:
1. struct Avatar definition with fields: char *name, struct Item *inventory, and struct Room *location.
2. create_player(): Function to create the avatar.
3. inventory(): Prints the avatar's inventory list of items.
4. take(): Takes the item from the avatar's current location and adds it to their inventory.
5. drop(): Drops an item from the avatar's inventory and adds it to the room they're in.
6. look(): Allows the avatar to view information about the room that they're in.
7. move_player(): Allows the user to move the avatar into a valid room in a provided direction.

clue.c:
1. create_answer(): Allocates memory to create a Clue struct and iniitializes its fields. Assigns a random weapon, room, and murderer to the Clue struct. Takes in a char **, struct Item**, and struct Room** argument.
2. clue(): Allows the user to guess the solution to the game. Takes in a struct Clue *, struct Room **, struct Avatar *, char *character, and char *item argument. Iterates through the 9 rooms, 5 characters, and 6 items to
   check if there is a match to the game's solution. Moves the character chosen to the room that the avatar is currently in. Increments a correctGuess counter if the room, weapon, and crime scene match the answer.

clue.h:
1. struct Clue definition with fields: struct Item *weapon, struct Room *room, and char *murderer.
2. create_answer(): Creates a Clue struct with provided char **characters, struct Item **items, and struct Room *rooms.

rooms.c:
1. create_room(): Allocates memory to create a Room sturct and initalizes its fields. Takes in a char* argument representing the name of the room.
2. room_dir(): Prints out the surrounding rooms to the struct Room *curRoom argument if they're not NULL.
3. room_chars(): Prints out the list of characters in the struct Room *curRoom argument.
4. room_items(): Prints out the item list of the struct Room *curRoom argument.
5. create_gameboard(): Creates the game board and links the rooms together. Takes in a struct Room **rooms argument which represents the rooms to link. The rooms' north, west, east, and south pointers are assigned.
6. item_insert(): Function to randomly insert 6 items into 6 random rooms. Takes in a struct Item **items and struct Room **rooms argument, which represent the list of items to insert and the rooms to insert them into.
7. char_insert(): Function to randomly insert 5 characters into 5 random rooms. Takes in a char **characterNames and struct Room **rooms argument, which represent the characters to insert and the rooms to insert them into.

rooms.h:
1. Create a struct Room with fields: name, North, South, East, West, itemList, and character.
2. Create a struct Avatar with fields: inventory and location.
3. Create a struct Clue with the fields: weapon, room, and murderer.
4. create_gameboard();
5. randomize_rooms();
6. randomize_characters();

adventure.c:
1. listObjects: A test function to ensure that the game board has been constructed correctly. Prints out the gameboard's directional rooms and calls room_chars() and room_items().
   Takes in a struct Room ** as an argument whose fields will be printed out.
2. list(): A function that prints out the room names, item names, and character names in the game. Takes in a struct Room **, struct Item **, and char ** argument whose names will be printed.
3. randomize_rooms(): A function that randomizes the char[] array of room names. Takes in a char ** argument, which is the char[] array of Room names.
4. randomize_characters(): A function that randomizes the char[] array of character names. Takes in a char ** argument, which is the char[] array of character names.
5. randomzie_items(): A function that randomizes the item[] array of item names. Takes in a char ** argument, which is the char[] array of item names.
6. main(): Contains the game implementation. First creates 3 char[] arrays with the room, item, and character names, and calls each respective randomize() function to randomize the names.
   The game board is created by calling create_gameboard(), items are randomly inserted into the rooms using the item_insert() function, and characters are randomly inserted into the rooms
   using the char_insert() function. A Clue struct is created with a randomly generated solution to the game. The game solution's murderer, weapon, and crime scene are printed out. The Avatar struct
   is created and placed into a random room. The avatar's location field is updated to the room that it is placed in. The user inputs commands that are tracked in if, else statements.
   
   Commands:
   "help" - show list of commands
   "list" - show list of items, rooms, and characters
   "look" - show list of characters, surrounding rooms, current location, and items in the room you are in
   "go" - allows movement of the avatar to the north, south, east, or west rooms if they are not NULL
   "take" - allows the item to be picked up into the avatar's inventory if there is an item present in the current room
   "drop" - allows the item to dropped out of the avatar's inventory and into the avatar's current room
   "inventory" - lists the items in the avatar's inventory
   "clue" - allows the user to make a guess on who is the murderer, the weapon used, and what the crime scene location is
   
   The user has 10 tries to make a guess about the crime details. The user loses if they cannot make the correct guess in 10 tries.

