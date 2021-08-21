#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/users.h"
#include "../include/playlists.h"


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

struct playlists_list
{
	int size;
	Playlist *head;
	Playlist *tail;
};

struct playlist
{
	int index;
	char *name;
	Playlist *prev;
	Playlist *next;
	int size;
	Music *head;
	Music *tail;
};

struct music
{
	int index;
	char *artist;
	char *name;
	Music *next;
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


/* -------------- General Manipulation -------------- */
void refactPlayED(UsersList *users)
{
	User *usr = NULL;
	PlaylistList *refactPlaylists = NULL;
	Playlist *pl = NULL;
	/*char playlistName[80] = "", artistName[80] = "";

	usr = users->first;
	while (usr != NULL)
	{
		PlaylistList *oldplaylists = usr->playlists;
		refactPlaylists = initPlaylistList();

		pl = (usr->playlists)->head;
		while (pl != NULL)
		{
			Music *msc = pl->head;
			while (msc != NULL)
			{
				Playlist *rpl = refactPlaylists->head; // iterate for all new playlists
				Playlist *npl = NULL;
				strcpy(artistName, msc->artist); // save artist name
				strcat(artistName, ".txt");
				strcpy(playlistName, artistName); // create playlist name

				if (rpl == NULL)
				{
					npl = initPlaylist(playlistName);
					addMusicToTail(npl, msc);
					addPlaylistToTail(refactPlaylists, npl);
					refactPlaylists->size += 1;
					msc = msc->next;
				}
				while (rpl != NULL)
				{
					if (strcmp(playlistName, rpl->name) != 0) // if the playlist with the artist name was not created...
					{
						npl = initPlaylist(playlistName); // [...] create new playlist
						addMusicToTail(npl, msc); // add music
						addPlaylistToTail(refactPlaylists, npl); // save playlist
						refactPlaylists->size += 1;
					}
					else
					{
						addMusicToTail(rpl, msc); // just add music to existent playlist
					}

					rpl = rpl->next;
				}

				msc = msc->next;
			}

			pl = pl->next;
		}
		destroyPlaylistList(oldplaylists);
		usr->playlists = refactPlaylists;

		usr = usr->next;
	}*/


	FILE *refact_of = fopen("./output/played-refatorada.txt", "w+");

	usr = users->first;
	while (usr != NULL)
	{
		fprintf(refact_of, "%s;%d;", usr->name, (usr->playlists)->size);
		pl = (usr->playlists)->head;
		while (pl != NULL)
		{
			if (pl->next != NULL)
				fprintf(refact_of, "%s;", pl->name);
			else if (usr->next != NULL)
				fprintf(refact_of, "%s\n", pl->name);
			else
				fprintf(refact_of, "%s", pl->name);
			pl = pl->next;
		}
		usr = usr->next;
	}

	fclose(refact_of);
}

void printSimilarities(UsersList *users)
{
	FILE *similarity_of = fopen("./output/similaridades.txt", "w+");

	//

	fclose(similarity_of);
}
