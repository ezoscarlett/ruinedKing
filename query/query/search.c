#include <stdio.h>
#include "load.h"

struct student* search(struct student *head, int queryNum)
{
	struct student *result = NULL;

	while (head != NULL)
	{
		if (head->num == queryNum)
		{
			result = head;
			break;
		}
		head = head->next;
	}
	return result;
}
