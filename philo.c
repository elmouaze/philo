/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:41:54 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/03 21:31:30 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

int check_death(p_info *arg)
{
	int i = 0;
	t_philo *philos = arg->philos;
	
	while (1)
	{
		printf("*--*-*-*-*-*-*%p\n",&arg->dead);
		if ((get_time() - philos[i].last_meal) >= arg->tt_die && arg->dead != 1)
		{
			pthread_mutex_lock(&arg->dead_lock);
			arg->dead = 1;
			usleep(1000);
			pthread_mutex_unlock(&arg->dead_lock);
			printf("%lld %d  has died\n", (get_time() - philos[i].start) ,philos[i].id);
			return (0);
		}
		pthread_mutex_lock(&arg->meal_eaten);
		if (arg->meals == arg->philos_number)
		{
			arg->dead = 1;
			pthread_mutex_unlock(&arg->meal_eaten);
			pthread_mutex_unlock(&arg->dead_lock);
			return (0);
		}
		pthread_mutex_unlock(&arg->meal_eaten);
		pthread_mutex_unlock(&arg->dead_lock);
		if (i + 1 == arg->philos_number)
			i = 0;
	}
	return (1);
}

int get_death_status(p_info *info)
{
	pthread_mutex_lock(&info->dead_lock);
	if (info->dead == 1)
	{
		//printf("*--*-*-*-*-*-*%p\n",&info->dead);
		pthread_mutex_unlock(&info->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&info->dead_lock);
	return 1;
}

void *routine(void *args)
{
	t_philo *philo;
	
	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
	{
		print_message(" is thinking\n",philo->id,&(philo->infos->print_lock),philo);
		ft_usleep(philo->infos->tt_eat);
	}
	while(get_death_status(philo->infos))
	{
		pthread_mutex_lock(philo->fork_l);
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo);
		pthread_mutex_lock(&(philo->fork_r));
		print_message(" has taken a fork\n",philo->id,&(philo->infos->print_lock),philo);
		print_message(" is eating\n",philo->id,&(philo->infos->print_lock),philo);
		philo->last_meal = get_time();
		philo->m_count++;
		ft_usleep(philo->infos->tt_eat);
		if (philo->m_count == philo->infos->eat_cond)
		{
			pthread_mutex_lock(&(philo->infos->meal_eaten));
			philo->infos->meals++;
			pthread_mutex_unlock(&(philo->infos->meal_eaten));		
		}
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		print_message(" is sleeping\n",philo->id,&(philo->infos->print_lock),philo);
		ft_usleep(philo->infos->tt_sleep);
		print_message(" is thinking\n",philo->id,&(philo->infos->print_lock),philo);
	}
	return (NULL);
}

void init_philo(p_info *info)
{
	int i = 0;

	pthread_mutex_init(&(info->dead_lock),NULL);
	pthread_mutex_init(&(info->meal_eaten), NULL);
	pthread_mutex_init(&(info->print_lock), NULL);
	info->philos = malloc (sizeof(t_philo) * info->philos_number);
	while (i < info->philos_number)
	{	
		info->philos[i].id = i+1;
		info->philos[i].m_count = 0;
		info->philos[i].infos = info;
		info->philos[i].start = get_time();
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
		pthread_detach(tid[i]); 
		i++;
	}
	check_death(info);
	i = -1;
	while (++i < info->philos_number)
		pthread_mutex_destroy(&info->philos[i].fork_r);
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->meal_eaten);
	pthread_mutex_destroy(&info->print_lock);
	// if(info->dead == -1)
	// {
	// 	if (info->died_philo > 0)	
	// 		printf("%lld %d  %s", info->time_of_death , \
	// 				info->died_philo, "died\n");
	// }
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