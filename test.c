#include "philosphers.h"

int main ()
{
	struct timeval curr;
	gettimeofday(&curr,NULL);
	printf("%ld in ms= %d\n",curr.tv_sec,curr.tv_usec);
}