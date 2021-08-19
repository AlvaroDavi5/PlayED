#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"


struct users_list
{
	int size;
	User *first;
	User *last;
};

struct usr
{
	int index;
	char *name;
	FriendList *friends;
	PlaylistList *playlists;
	User *next;
};


/* -------------- User Manipulation -------------- */
User * registerUser(char *name)
{
	User *user = (User *) malloc(sizeof(User));

	user->index = -1;
	user->name = strdup(name);
	user->friends = initFriendList();
	user->playlists = initPlaylistList();
	user->next = NULL;

	return user;
}

void showUser(User *user)
{
	printf("%s \n", user->name);
}


/* -------------- UsersList Manipulation -------------- */
UsersList * initUsersList()
{
	UsersList *list = (UsersList *) malloc(sizeof(UsersList));

	list->size = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

void addUserToTail(UsersList *list, User *usr)
{
	usr->next = NULL;

	if (list->first == NULL)
	{
		list->first = usr;
	}
	else
	{
		list->last->next = usr;
	}

	usr->index = list->size;
	list->last = usr;
	list->size += 1;
}

User * getUserByPosition(UsersList *list, fptrCompare compareFunction, int position)
{
	User *current = list->first;

	while (current != NULL)
	{
		if (compareFunction((current)->index, position) == 0)
		{
			return current;
		}

		current = (current)->next;
	}

	return NULL;
}

User * getUserByName(UsersList *list, char *name)
{
	User *current = list->first;

	while (current != NULL)
	{
		if (strcmp((current)->name, name) == 0)
		{
			return current;
		}

		current = (current)->next;
	}

	return NULL;
}

void deleteUser(UsersList *list, User *usr)
{
	User *current = list->first;

	if (usr == list->first)
	{
		if (list->first->next == NULL)
		{
			list->first = list->last;
		}
		else
		{
			list->first = list->first->next;
		}
	}
	else
	{
		while (current != NULL && (current)->next != usr)
		{
			current = (current)->next;
		}
		if (current != NULL && (current)->next == usr)
		{
			(current)->next = usr->next;
			((current)->next)->index = usr->index;
		}
	}

	free(usr->name);
	destroyFriendList(usr->friends);
	destroyPlaylistList(usr->playlists);
	free(usr);
	list->size -= 1;

	User *indexedUser = list->first;
	for (int i = 0; i < list->size; i++)
	{
		if (indexedUser != NULL)
		{
			indexedUser->index = i;
			indexedUser = indexedUser->next;
		}
	}
}

void destroyUsersList(UsersList *list)
{
	User *current = list->first;
	User *next = NULL;

	while (current != NULL)
	{
		next = (current)->next;

		deleteUser(list, current);
		current = next;
	}

	free(list);
}

void displayUsersList(UsersList *list)
{
	User *current = list->first;

	while (current != NULL)
	{
		printf("User %d: \n", (current)->index);
		showUser(current);
		current = (current)->next;
	}
}


/* -------------- Another Functions -------------- */
void readUserAndFriends(FILE *input_file, UsersList *list)
{
	int count = 0; // user counter
	char c = ' '; // iteration character
	char userName[80] = "", friendName[80] = ""; // names store
	User *usr = NULL; // user general pointer
	Friend *fnd = NULL; // friend general pointer

	while (c != EOF && c != '\n') // while its not End Of File, read first line and...
	{
		fscanf(input_file, "%[^;,\n]", userName); // store string between ';' as username
		c = fgetc(input_file); // [...] continue reading

		usr = registerUser(userName);
		addUserToTail(list, usr); // creating and saving users

		usr = NULL;
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		if (i > 0) // skip first line
		{
			fscanf(input_file, "%[^;];%[^\n]", userName, friendName);
			usr = getUserByName(list, userName);
			fnd = makeFriend(getUserByName(list, friendName));

			if (usr != NULL && fnd != NULL)
			{
				addFriendToTail(usr->friends, fnd);
				addFriendToTail(returnUser(fnd)->friends, makeFriend(usr));
			}
		}
	}
	free(fnd);

	fclose(input_file);
}

void readAndCreatePlaylists(FILE *input_file, UsersList *list)
{
	int playlistNum, lineCount = 0, line = 0, i = 0;
	char c = ' ';
	char userName[80] = "", playlistName[80] = "";
	User *usr = NULL;
	Playlist *pl = NULL;

	rewind(input_file);
	// counting lines
	while (c != EOF)
	{
		c = fgetc(input_file);
		if (c == '\n')
			line++;
	}
	lineCount =  line+1;
	rewind(input_file); // reseting file pointer (to read again)

	for (int l = 0; l < lineCount; l++)
	{
		fscanf(input_file, "%[^;];%d", userName, &playlistNum); // reading user and number of playlist

		usr = list->first;
		while (usr != NULL) // runs through all users
		{
			if ((strcmp(userName, usr->name)) == 0)
			{
				for (i = 0; i < playlistNum; i++)
				{
					// reading playlist name
					if (i != playlistNum-1)
						fscanf(input_file, ";%[^;]", playlistName);
					else
						fscanf(input_file, ";%[^\n]", playlistName);

					pl = initPlaylist(playlistName);
					addPlaylistToTail(usr->playlists, pl);
				}
			}
			fscanf(input_file, "\n");

			usr = usr->next;
		}
	}

	fclose(input_file);
}

int compareValue(int n1, int n2)
{
	if (n1 == n2)
	{
		return 0;
	}
	else if (n2 > n1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
