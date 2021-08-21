#ifndef _UTILS_H

	#define _UTILS_H

	#include <stdio.h>
	#include <stdlib.h>
	// OS verification
	#ifdef __unix__
		#include <unistd.h> // to system commands and manipulations on UNIX based OS (Linux, GNU, BSD...)
		#define MAKEDIR "mkdir " // define command to create directory
	#elif defined(_WIN32) || defined(WIN32)
		#include <windows.h> // to system commands and manipulations on MS-DOS based OS (Windows versions)
		#define MAKEDIR "md "
	#endif
	#include "users.h"
	#include "playlists.h"
	#include "friendship.h"

	#define FALSE 0
	#define TRUE 1


	// -------------- System Navigation and File Manipulation Functions --------------
	/**
		* Read the userlist and user friendlist file to create users with friendship relation
		* @param FILE* - input_file
		* @param UsersList* - list
		* @return void
	**/
	void readUserAndFriends(FILE *input_file, UsersList *list);
	/**
		* Read the user playlists file and add to user profile
		* @param FILE* - input_file
		* @param UsersList* - list
		* @return void
	**/
	void readAndCreateUserPlaylists(FILE *input_file, UsersList *list);
	/**
		* Read the playlist music files and add musics to playlist
		* @param FILE* - input_file
		* @param Playlist* - playlist
		* @return void
	**/
	void readPlaylistMusics(FILE *input_file, Playlist *playlist);
	/**
		* Create specific directory to save output files
		* @param string - path
		* @param string - dirName
		* @return int
	**/
	int createDir(char *path, char *dirName);

	// -------------- System Navigation and File Manipulation Functions --------------
	/**
		* Remove spaces after string
		* @param string - str
		* @return char *
	**/
	char* removeLeadingSpaces(char* str);
	/**
		* Compare two values and return a status
		* @param int - n1
		* @param int - n2
		* @return 0: n2 == n1, 1: n2 > n1, -1: n2 < n1
	**/
	int compareValue(int n1, int n2);

#endif
