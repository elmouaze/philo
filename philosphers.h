#ifndef PHILOSOPHERS_H
# define  PHILOSOPHERS_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
#include <fcntl.h>
typedef  struct info p_info;
typedef struct philos
{
	int id;
	int m_count;
	long long last_meal;
	long long start;
	p_info *infos;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
}	t_philo;

typedef struct info{
	long philos_number;
	long tt_die;
	long tt_eat;
	int tt_sleep;
	int eat_cond;
	int flag;
	int dead;
	int meals;
	int start;
	int died_philo;
	long long time_of_death;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_eaten;
	pthread_mutex_t print_lock;
	t_philo *philos;

}	p_info;
void	print_message(char *str, int id, pthread_mutex_t *print_lock,t_philo *arg);
void ft_parse(int ac, char **values,p_info *ph);
size_t get_time();
int death_check(t_philo *arg);
void	ft_usleep(size_t t_ms);
int get_death_status(p_info *info);
#endif 
