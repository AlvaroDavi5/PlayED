#ifndef _FRIENDSHIP_H

	#define _FRIENDSHIP_H

	#include "playlists.h"
	#include "users.h"


	/* ---------------------------- Type Definitions ---------------------------- */

	// -------------- Abstract Data Types --------------
	/*
		size (int)
		Friend list pointers
		- first
		- last
	*/
	typedef struct friend_list FriendList;
	/*
		index (int)
		friend (User pointer)
		Friend pointer
		- next
	*/
	typedef struct friend Friend;
	// User ATD reimplemented
	typedef struct usr User;

	// -------------- Function Pointers --------------
	// receive int,int and return int
	typedef int (* fptrCompare)(int, int);



	/* ---------------------------- Function Prototypes ---------------------------- */

	// -------------- Friend Functions --------------
	/**
		* @param User* - usr
		* @return Friend *
	**/
	Friend * makeFriend(User *usr);
	/**
		* @param Friend* - friend
		* @return User *
	**/
	User * returnUser(Friend *friend);
	/**
		* @param User* - user
		* @param User* - friend
		* @return int
	**/
	int isFriend(User *user, User *friend);
	/**
		* @param Friend* - friend
		* @return void
	**/
	void showFriend(Friend *friend);

	// -------------- FriendList Functions --------------
	/**
		* @param void
		* @return FriendList *
	**/
	FriendList * initFriendList();
	/**
		* @param FriendList* - list
		* @param Friend* - fnd
		* @return void
	**/
	void addFriendToTail(FriendList *list, Friend *fnd);
	/**
		* @param FriendList* - list
		* @param fptrCompare - compareFunction
		* @param int - position
		* @return Friend *
	**/
	Friend * getFriendByPosition(FriendList *list, fptrCompare compareFunction, int position);
	/**
		* @param FriendList* - list
		* @param char* - name
		* @return Friend *
	**/
	Friend * getFriendByName(FriendList *list, char *name);
	/**
		* @param FriendList* - list
		* @param Friend* - fnd
		* @return void
	**/
	void deleteFriend(FriendList *list, Friend *fnd);
	/**
		* @param FriendList* - list
		* @return void
	**/
	void destroyFriendList(FriendList *list);
	/**
		* @param FriendList* - list
		* @return void
	**/
	void displayFriendList(FriendList *list);

#endif
