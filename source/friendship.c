#include <stdio.h>
#include <stdlib.h>
#include "friendship.h"


struct friend_list
{
	unsigned int size;
	Friend *head;
	Friend *tail;
};

struct friend
{
	unsigned int index;
	User *friend;
	Friend *next;
};


int noneFS()
{
	//

	return 0;
}

