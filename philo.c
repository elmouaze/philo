/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:41:54 by ael-moua          #+#    #+#             */
/*   Updated: 2024/10/26 03:11:59 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

int death_check(t_philo *arg)
{
	pthread_mutex_lock(&(arg->infos->dead_lock));
	if (arg->infos->dead == -1)
	{
		pthread_mutex_unlock(&(arg->infos->dead_lock));
		return -1;
	}
	pthread_mutex_unlock(&(arg->infos->dead_lock));	
	if (arg->infos->eat_cond > 0)
	{
		if (arg->m_count == arg->infos->eat_cond)
		{
			pthread_mutex_lock(&(arg->infos->meal_eaten));
			arg->infos->meals++;
			if (arg->infos->meals == arg->infos->philos_number)
			{
				pthread_mutex_lock(&arg->infos->dead_lock);
				arg->infos->dead = -1;
				arg->infos->died_philo = arg->id;
				arg->infos->time_of_death =  get_time() - arg->infos->start;
				pthread_mutex_unlock(&arg->infos->dead_lock);
				pthread_mutex_unlock(&(arg->infos->meal_eaten));
				return (-1);
			}
			pthread_mutex_unlock(&(arg->infos->meal_eaten));
		}
	}

	// if (get_time() - arg->last_meal >= arg->infos->tt_die)
	// {
	// 	arg->infos->dead = -1;
	// 	arg->infos->time_of_death = get_time() - arg->infos->start;
	// 	arg->infos->died_philo = arg->id;
	// 	pthread_mutex_unlock(&(arg->infos->meal_eaten));
	// 	return -1;
	// }
	pthread_mutex_unlock(&(arg->infos->meal_eaten));
	return 1;
}


void *routine(void *args)
{
	t_philo *philo;
	
	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		ft_usleep(philo->infos->tt_eat);
	while(death_check(philo) > 0)
	{
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo->infos->start,philo);
		pthread_mutex_lock(philo->fork_l);
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo->infos->start,philo);
		pthread_mutex_lock(&(philo->fork_r));
		print_message(" is eating\n",philo->id,&(philo->infos->print_lock),philo->infos->start,philo);
		philo->m_count++;
		ft_usleep(philo->infos->tt_eat);
		print_message(" is sleeping\n",philo->id,&(philo->infos->print_lock),philo->infos->start,philo);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_unlock(philo->fork_l);
		ft_usleep(philo->infos->tt_sleep );
		print_message(" is thinking\n",philo->id,&(philo->infos->print_lock),philo->infos->start,philo);
	}
	return (NULL);
}



void init_philo(p_info *info)
{
	int i = 0;

	info->philos = malloc (sizeof(t_philo) * info->philos_number);
	pthread_mutex_init(&(info->dead_lock),NULL);
	pthread_mutex_init(&(info->meal_eaten), NULL);
	pthread_mutex_init(&(info->print_lock), NULL);
	info->start =  get_time();
	while (i < info->philos_number)
	{	
		info->philos[i].id = i+1;
		info->philos[i].m_count = 0;
		info->philos[i].infos = info;
		info->meals = 0;
		info->philos[i].last_meal = get_time();
		pthread_mutex_init(&(info->philos[i].fork_r), NULL);
		if (i+1 == info->philos_number)
			info->philos[i].fork_l = &(info->philos[0].fork_r);
		else
			info->philos[i].fork_l = &(info->philos[i+1].fork_r);
		i++;
	}
}

void	start_simulation(p_info *info)
{
	int	i;
	pthread_t tid[info->philos_number + 1];

	i = 0;
	while (i < info->philos_number)
	{
		pthread_create(&(tid[i]), NULL, &routine, &info->philos[i]);
		i++;
	}
	i = 0;
	while (i < info->philos_number)
	{
		pthread_join(tid[i], NULL); 
		i++;
	}
	if(info->dead == -1)
	{
		if (info->died_philo > 0)	
			printf("%lld %d  %s", info->time_of_death , \
					info->died_philo, "died\n");
	}
}
int main(int ac, char **av)
{
	p_info info;
	if (ac == 5 || ac == 6)
	{
		ft_parse(ac , av, &info);
		if (info.flag == -1)
			return (printf("error in arguments"), 1);
		init_philo(&info);
		start_simulation(&info);
	}else
		printf("error in argument");
	return 0;
}