#include <stdio.h>
#include <load.h>

struct student search(struct student *array, int count, int queryNum)
{
	struct student result = NULL;
	int i;
	for (i = 0; i < count; i++)
	{
		if (array[i].num == queryNum)
		{
			result = &array[i];
		}
	}
	return result;
}
