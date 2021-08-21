#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/playlists.h"


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


/* -------------- Music Manipulation -------------- */
Music * createMusic(char *name, char *artist)
{
	Music *song = (Music *) malloc(sizeof(Music));

	song->index = -1;
	song->name = strdup(name);
	song->artist = strdup(artist);
	song->next = NULL;

	return song;
}

void displayMusic(Music *song)
{
	printf("%s - %s \n", song->artist, song->name);
}


/* -------------- Playlist Manipulation -------------- */
Playlist * initPlaylist(char *name)
{
	Playlist *playlist = (Playlist *) malloc(sizeof(Playlist));

	playlist->index = -1;
	playlist->name = strdup(name);
	playlist->prev = NULL;
	playlist->next = NULL;

	playlist->size = 0;
	playlist->head = NULL;
	playlist->tail = NULL;

	return playlist;
}

void addMusicToTail(Playlist *playlist, Music *song)
{
	song->next = NULL;

	if (playlist->head == NULL)
	{
		playlist->head = song;
	}
	else
	{
		playlist->tail->next = song;
	}

	song->index = playlist->size;
	playlist->tail = song;
	playlist->size += 1;
}

Music * getMusic(Playlist *playlist, fptrCompare compareFunction, int position)
{
	Music *current = playlist->head;

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

void deleteMusic(Playlist *playlist, Music *song)
{
	Music *current = playlist->head;

	if (song == playlist->head)
	{
		if (playlist->head->next == NULL)
		{
			playlist->head = playlist->tail;
		}
		else
		{
			playlist->head = playlist->head->next;
		}
	}
	else
	{
		while (current != NULL && (current)->next != song)
		{
			current = (current)->next;
		}
		if (current != NULL && (current)->next == song)
		{
			(current)->next = song->next;
			((current)->next)->index = song->index;
		}
	}

	free(song->artist);
	free(song->name);
	free(song);
	playlist->size -= 1;

	Music *indexedMusic = playlist->head;
	for (int i = 0; i < playlist->size; i++)
	{
		if (indexedMusic != NULL)
		{
			indexedMusic->index = i;
			indexedMusic = indexedMusic->next;
		}
	}
}

void destroyPlaylist(Playlist *playlist)
{
	Music *current = playlist->head;
	Music *next = NULL;

	while (current != NULL)
	{
		next = (current)->next;

		deleteMusic(playlist, current);
		current = next;
	}

	free(playlist->name);
	free(playlist);
}

void displayPlaylist(Playlist *playlist)
{
	printf(" --- %s --- \n", playlist->name);

	Music *current = playlist->head;

	while (current != NULL)
	{
		displayMusic(current);
		current = (current)->next;
	}
}


/* -------------- PlaylistList Manipulation -------------- */
PlaylistList * initPlaylistList()
{
	PlaylistList *list = (PlaylistList *) malloc(sizeof(PlaylistList));

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

void addPlaylistToTail(PlaylistList *list, Playlist *pl)
{
	pl->next = NULL;

	if (list->head == NULL)
	{
		list->head = pl;
	}
	else
	{
		list->tail->next = pl;
	}

	pl->index = list->size;
	pl->prev = list->tail;
	list->tail = pl;
	list->size += 1;
}

Playlist * getPlaylist(PlaylistList *list, fptrCompare compareFunction, int position)
{
	Playlist *current = list->head;

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

void deletePlaylist(PlaylistList *list, Playlist *pl)
{
	Playlist *current = list->head;

	if (pl == list->head)
	{
		if (list->head->next == NULL)
		{
			list->head = list->tail;
		}
		else
		{
			list->head = list->head->next;
		}
	}
	else
	{
		while (current != NULL && (current)->next != pl)
		{
			current = (current)->next;
		}
		if (current != NULL && (current)->next == pl)
		{
			(current)->next = pl->next;
			(current->next)->prev = pl->prev;
			((current)->next)->index = pl->index;
		}
	}

	destroyPlaylist(pl);
	list->size -= 1;

	Playlist *indexedPlaylist = list->head;
	for (int i = 0; i < list->size; i++)
	{
		if (indexedPlaylist != NULL)
		{
			indexedPlaylist->index = i;
			indexedPlaylist = indexedPlaylist->next;
		}
	}
}

void destroyPlaylistList(PlaylistList *list)
{
	Playlist *current = list->head;
	Playlist *next = NULL;

	while (current != NULL)
	{
		next = (current)->next;

		deletePlaylist(list, current);
		current = next;
	}

	free(list);
}

void displayPlaylistList(PlaylistList *list)
{
	Playlist *current = list->head;

	while (current != NULL)
	{
		printf("Playlist %d: \n", (current)->index);
		displayPlaylist(current);
		current = (current)->next;
	}
}
