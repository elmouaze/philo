/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:41:54 by ael-moua          #+#    #+#             */
/*   Updated: 2024/10/11 21:27:26 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"
int death_check(t_philo *arg)
{
	if (arg->infos->eat_cond > 0)
	{
		if (arg->m_count == arg->infos->eat_cond)
		{
			pthread_mutex_lock(&(arg->infos->meal_eaten));
			arg->infos->meals++;
			if (arg->infos->meals == arg->infos->philos_number)
			{		
				pthread_mutex_unlock(&(arg->infos->meal_eaten));
				arg->infos->dead = -1; 
				return (-1);
			}
			pthread_mutex_unlock(&(arg->infos->meal_eaten));
		}
	}
	return 1;
}


void *routine(void *args)
{
	t_philo *philo;
	
	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep(55 * 1000);
	while(death_check(philo) > 0 && philo->infos->dead > 0)
	{
		pthread_mutex_lock(philo->fork_l);
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo->infos->start);
		pthread_mutex_lock(&(philo->fork_r));
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo->infos->start);
		print_message(" is eating\n",philo->id,&(philo->infos->print_lock),philo->infos->start);
		philo->m_count++;
		usleep(philo->infos->tt_eat * 1000);
		print_message(" is sleeping\n",philo->id,&(philo->infos->print_lock),philo->infos->start);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_unlock(philo->fork_l);
		usleep(philo->infos->tt_sleep * 1000);
		print_message(" is thinking\n",philo->id,&(philo->infos->print_lock),philo->infos->start);
	}
	return NULL;
}

long long get_time()
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000)+(time.tv_usec / 1000));
}


void init_philo(p_info *info)
{
	int i = 0;
	pthread_t tid[info->philos_number + 1];
	
	info->philos = malloc (sizeof(t_philo) * info->philos_number);
	info->start =  get_time();
	while (i < info->philos_number)
	{	
		info->philos[i].id = i+1;
		info->philos[i].m_count = 0;
		info->philos[i].infos = info;
		info->meals = 0;
		info->philos[i].last_meal = 0;
		pthread_mutex_init(&(info->philos[i].fork_r), NULL);
		if (i+1 == info->philos_number)
			info->philos[i].fork_l = &(info->philos[0].fork_r);
		else
			info->philos[i].fork_l = &(info->philos[i+1].fork_r);
		pthread_create(&(tid[i]), NULL, &routine, &info->philos[i]);
		i++;
	}
	i = 0;
	while (i < info->philos_number )
	{
		pthread_join(tid[i], NULL); 
		i++;
	}
}

int main(int ac, char **av)
{
	p_info info;
	if (ac == 5 || ac == 6)
	{
		ft_parse(ac , av, &info);
		if (info.flag == -1)
			return (printf("error in arguments"),1);
		init_philo(&info);
	}else
	{
		printf("error in argument");
	}
	return 0;
}