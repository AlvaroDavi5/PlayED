#include <stdio.h>
#include <stdlib.h>
#include "playlists.h"


struct playlists_list
{
	unsigned int size;
	Playlist *head;
	Playlist *tail;
};

struct playlist
{
	unsigned int index;
	char *name;
	Playlist *prev;
	Playlist *next;
	unsigned int size;
	Music *head;
	Music *tail;
};

struct music
{
	unsigned int index;
	char *artist;
	char *name;
	Music *next;
};


int nonePL()
{
	//

	return 0;
}

