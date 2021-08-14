#ifndef _PLAYLISTS_H

	#define _PLAYLISTS_H


	/* ---------------------------- Type Definitions ---------------------------- */

	// -------------- Abstract Data Types --------------
	/*
		size (int)
		Playlist list pointers
		- head
		- tail
	*/
	typedef struct playlists_list PlaylistList;
	/*
		index (int)
		name (string)
		Playlist pointers
		- prev
		- next

		size (int)
		Music list pointers
		- head
		- tail
	*/
	typedef struct playlist Playlist;
	/*
		index (int)
		artist (string)
		name (string)
		Music pointer
		- next
	*/
	typedef struct music Music;

	// -------------- Function Pointers --------------
	// receive int,int and return int
	typedef int (* fptrCompare)(int, int);



	/* ---------------------------- Function Prototypes ---------------------------- */

	// -------------- Music Manipulation --------------
	/**
		* @param string - name
		* @param string - artist
		* @return Music *
	**/
	Music * createMusic(char *name, char *artist);
	/**
		* @param Music * - song
		* @return void
	**/
	void displayMusic(Music *song);

	// -------------- Playlist Manipulation --------------
	/**
		* @param string - name
		* @return Playlist *
	**/
	Playlist * initPlaylist(char *name);
	/**
		* @param Playlist* - playlist
		* @param Music* - song
		* @return void
	**/
	void addMusicToHead(Playlist *playlist, Music *song);
	/**
		* @param Playlist* - playlist
		* @param Music* - song
		* @return void
	**/
	void addMusicToTail(Playlist *playlist, Music *song);
	/**
		* @param Playlist* - playlist
		* @param fptrCompare - compareFunction
		* @param int - position
		* @return Music *
	**/
	Music * getMusic(Playlist *playlist, fptrCompare compareFunction, int position);
	/**
		* @param Playlist* - playlist
		* @param Music* - song
		* @return void
	**/
	void deleteMusic(Playlist *playlist, Music *song);
	/**
		* @param Playlist* - playlist
		* @return void
	**/
	void destroyPlaylist(Playlist *playlist);
	/**
		* @param Playlist* - playlist
		* @return void
	**/
	void displayPlaylist(Playlist *playlist);

	// -------------- PlaylistList Manipulation --------------
	/**
		* @param void
		* @return PlaylistList *
	**/
	PlaylistList * initPlaylistList();
	/**
		* @param PlaylistList* - list
		* @param Playlist* - pl
		* @return void
	**/
	void addPlaylistToHead(PlaylistList *list, Playlist *pl);
	/**
		* @param PlaylistList* - list
		* @param Playlist* - pl
		* @return void
	**/
	void addPlaylistToTail(PlaylistList *list, Playlist *pl);
	/**
		* @param PlaylistList* - list
		* @param Playlist* - pl
		* @return Playlist *
	**/
	Playlist * getPlaylist(PlaylistList *list, fptrCompare compareFunction, int position);
	/**
		* @param PlaylistList* - list
		* @param Playlist* - pl
		* @return void
	**/
	void deletePlaylist(PlaylistList *list, Playlist *pl);
	/**
		* @param PlaylistList* - list
		* @return void
	**/
	void destroyPlaylistList(PlaylistList *list);
	/**
		* @param PlaylistList* - list
		* @return void
	**/
	void displayPlaylistList(PlaylistList *list);

#endif
