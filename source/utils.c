#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/users.h"
#include "../include/playlists.h"
#include "../include/friendship.h"


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


/* -------------- SO Nav and File Manip Functions -------------- */
int createDir(char *path, char *dirName)
{
	char command[140] = "";

	strcpy(command, MAKEDIR); // define command to make directory
	strcat(command, path); // concatenate path
	strcat(command, dirName); // concatenate directory name

	if (system(command)) // execute command
		return TRUE;
	else
		return FALSE;
}

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

void readAndCreateUserPlaylists(FILE *input_file, UsersList *list)
{
	int playlistNum, lineCount = 0, line = 0, i = 0;
	char c = ' ';
	char userName[80] = "", playlistName[80] = "", filePath[120] = "";
	User *usr = NULL;
	Playlist *pl = NULL;
	FILE *musics_if = NULL;

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

					strcpy(filePath, "./input/");
					strcat(filePath, playlistName);
					musics_if = fopen(filePath, "r");
					if (musics_if == NULL)
					{
						printf("Error to open '%s' file, exiting! \n", filePath);
						exit(1);
					}
					else
					{
						readPlaylistMusics(musics_if, pl); // load musics
					}
					strcpy(filePath, "./input/");
				}
			}
			fscanf(input_file, "\n");

			usr = usr->next;
		}
	}

	fclose(input_file);
}

void readPlaylistMusics(FILE *input_file, Playlist *playlist)
{
	char c = ' ';
	int count = 0; // music counter
	char musicName[90] = "", artistName[80] = "";
	Music *msc = NULL;

	rewind(input_file);
	while (c != EOF)
	{
		if (c == '\n')
			count += 1;

		c = fgetc(input_file);

		if (c == EOF)
			count++;
	}
	rewind(input_file);

	for (int i = 0; i < count; i++)
	{
		fscanf(input_file, "%[^-] - %[^\n]\n", artistName, musicName);
		strcpy(artistName, removeLeadingSpaces(artistName));

		msc = createMusic(musicName, artistName);
		addMusicToTail(playlist, msc);

		strcpy(artistName, "");
		msc = NULL;
	}

	fclose(input_file);
}

/* -------------- Another Functions -------------- */
char* removeLeadingSpaces(char* str)
{
	static char strout[99];
	int count = 0, j = 0, k = 0;

	while (str[count] == ' ') // iterate String until last leading space character
	{
		count++;
	}

	for (j = count, k = 0; str[j] != '\0'; j++, k++)
	{
		strout[k] = str[j];
	}
	strout[k] = '\0';

	return strout;
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