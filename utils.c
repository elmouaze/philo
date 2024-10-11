

#include "philosphers.h"

void	print_message(char *str, int id, pthread_mutex_t *print_lock,long long start)
{
	
	pthread_mutex_lock(print_lock);

	printf("%lld %d %s", get_time() - start ,id, str);
	pthread_mutex_unlock(print_lock);
}