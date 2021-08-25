#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/users.h"
#include "../include/playlists.h"
#include "../include/friendship.h"


int main()
{
	UsersList *users = initUsersList(); // initialized userlist


	readUserAndFriends("./input/amizade.txt", users); // read friendship input file
	readAndCreateUserPlaylists("./input/playlists.txt", users); // read playlists input file

	createFolder("./", "output");
	refactPlayED(users);
	printSimilarities(users);


	// freeing memory
	destroyUsersList(users);

	return 0;
}
