#ifndef PHILOSOPHERS_H
# define  PHILOSOPHERS_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef  struct info p_info;
typedef struct philos
{
	int id;
	int m_count;
	long long last_meal;
	p_info *infos;

	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
}	t_philo;

typedef struct info{
	int philos_number;
	int tt_die;
	int tt_eat;
	int tt_sleep;
	int eat_cond;
	long long start;
	int flag;
	int dead;
	int meals;
	pthread_mutex_t meal_eaten;
	pthread_mutex_t print_lock;
	t_philo *philos;

}	p_info;
void	print_message(char *str, int id, pthread_mutex_t *print_lock, long long start);
void ft_parse(int ac, char **values,p_info *ph);
long long get_time();

#endif 
