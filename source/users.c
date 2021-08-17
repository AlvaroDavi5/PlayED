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

void addUserToHead(UsersList *list, User *usr)
{
	if (list->first == NULL)
	{
		list->last = usr;
		usr->next = NULL;
	}
	else
	{
		usr->next = list->first;
	}

	list->first = usr;
	list->size += 1;

	User *current = list->first;
	for (int i = 0; i < list->size; i++)
	{
		(current)->index = i;
		current = (current)->next;
	}
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
	//destroyPlaylistList(usr->playlists);
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
	User *usr = NULL, *fndu = NULL; // user general pointer
	Friend *fnd = NULL; // friend general pointer

	while (c != '\n' && c != EOF) // read first line while its not End Of File...
	{
		fscanf(input_file, "%[^;,\n]", userName); // store string between ';' as username
		usr = registerUser(userName);
		usr->friends = initFriendList();
		addUserToTail(list, usr); // creating and saving users

		c = fgetc(input_file); // [...] continue reading
		usr = NULL;
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		if (i > 0) // skip first line
		{
			fscanf(input_file, "%[^;];%[^\n]", userName, friendName);
			usr = getUserByName(list, userName);
			fndu = getUserByName(list, friendName);
			fnd = makeFriend(fndu);

			if (usr != NULL && fndu != NULL)
				addFriendToTail(usr->friends, fnd);
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
