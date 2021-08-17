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
		name (string)
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
		* @param string - name
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
	void addUserToHead(UsersList *list, User *usr);
	void addUserToTail(UsersList *list, User *usr);
	/**
		* @param UsersList*
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

	// -------------- Another Functions --------------
	/**
		* Read the userlist and his friends list and create users with friendship relation
		* @param FILE* - input_file
		* @param UsersList* - list
		* @return void
	**/
	void readUserAndFriends(FILE *input_file, UsersList *list);
	/**
		* Compare two values and return a status
		* @param int - n1
		* @param int - n2
		* @return 0: n2 == n1, 1: n2 > n1, -1: n2 < n1
	**/
	int compareValue(int n1, int n2);

#endif
