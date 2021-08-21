#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/users.h"
#include "../include/playlists.h"
#include "../include/friendship.h"


int main()
{
	UsersList *users = initUsersList(); // initialized userlist
	// opening base files
	FILE *friendship_if = fopen("./input/amizade.txt", "r"); // friendship input file
	FILE *playlists_if = fopen("./input/playlists.txt", "r"); // playlists input file

	if (friendship_if == NULL || playlists_if == NULL) // check if the files do not exist
	{
		printf("Error to open 'amizade.txt' and 'playlists.txt' files, exiting!\n");
		exit(1);
	} // else...


	readUserAndFriends(friendship_if, users);
	readAndCreateUserPlaylists(playlists_if, users);

	createDir("./", "output");
	displayUsersList(users);
	refactPlayED(users);


	// freeing memory
	destroyUsersList(users);

	return 0;
}
