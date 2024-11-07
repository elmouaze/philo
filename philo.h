/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 05:58:02 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/05 10:37:55 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <fcntl.h>

typedef struct info	t_info;
typedef struct philos
{
	int					id;
	_Atomic int			m_count;
	_Atomic long long	last_meal;
	t_info				*infos;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
}	t_philo;

typedef struct info
{
	long			n_philo;
	long			tt_die;
	long			tt_eat;
	int				tt_sleep;
	int				eat_cond;
	int				flag;
	_Atomic int		dead;
	long long		start;
	int				meals;
	int				died_philo;
	long long		time_of_death;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_eaten;
	pthread_mutex_t	print_lock;
	t_philo			*philos;

}			t_info;

void		print_message(char *str, int id, \
pthread_mutex_t *print_lock, t_philo *arg);
void		ft_parse(int ac, char **values, t_info *ph);
long long	get_time(void);
int			*death_check(t_info *arg);
void		ft_usleep(size_t t_ms);
int			get_death_status(t_info *info);
void		start_simulation(t_info *info);
void		destroy_all(t_info *info, int size);
void		destroy_mutex(t_info *info, int count);

#endif
