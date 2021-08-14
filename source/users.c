#include <stdio.h>
#include <stdlib.h>
#include "users.h"


struct users_list
{
	unsigned int size;
	User *first;
	User *last;
};

struct usr
{
	unsigned int index;
	char *name;
	Friendlist *friends;
	PlaylistList *playlists;
	User *next;
};


int noneUS()
{
	//

	return 0;
}

