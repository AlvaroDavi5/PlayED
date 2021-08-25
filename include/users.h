#ifndef _USERS_H

	#define _USERS_H

	#include "playlists.h"
	#include "friendship.h"


	/* ---------------------------- Type Definitions ---------------------------- */

	// -------------- Abstract Data Types --------------
	/*
		size (int)
		User list pointers
		- first
		- last
	*/
	typedef struct users_list UsersList;
	/*
		index (int)
		name (char*)
		friends (Friendlist pointer)
		playlists (PlaylistList pointer)
		User pointer
		- next
	*/
	typedef struct usr User;

	// -------------- Function Pointers --------------
	// receive int,int and return int
	typedef int (* fptrCompare)(int, int);



	/* ---------------------------- Function Prototypes ---------------------------- */

	// -------------- User Functions --------------
	/**
		* @param char* - name
		* @return User *
	**/
	User * registerUser(char *name);
	/**
		* @param User* - user
		* @return void
	**/
	void showUser(User *user);

	// -------------- UsersList Functions --------------
	/**
		* @param void
		* @return UsersList *
	**/
	UsersList * initUsersList();
	/**
		* @param UsersList* - list
		* @param User* - usr
		* @return void
	**/
	void addUserToTail(UsersList *list, User *usr);
	/**
		* @param UsersList* - list
		* @param fptrCompare - compareFunction
		* @param int - position
		* @return User *
	**/
	User * getUserByPosition(UsersList *list, fptrCompare compareFunction, int position);
	/**
		* @param UsersList*
		* @param char* - name
		* @return User *
	**/
	User * getUserByName(UsersList *list, char *name);
	/**
		* @param UsersList* - list
		* @param User* - usr
		* @return void
	**/
	void deleteUser(UsersList *list, User *usr);
	/**
		* @param UsersList* - list
		* @return void
	**/
	void destroyUsersList(UsersList *list);
	/**
		* @param UsersList* - list
		* @return void
	**/
	void displayUsersList(UsersList *list);

	// -------------- General Functions --------------
	/**
		* @param UsersList* - users
		* @return void
	**/
	void refactPlayED(UsersList *users);
	/**
		* @param char* - userName
		* @param User* - list
		* @return void
	**/
	void buildUserPlaylistsFolder(char *userName, PlaylistList *list);
	/**
		* @param UsersList* - users
		* @return void
	**/
	void printSimilarities(UsersList *users);

#endif
