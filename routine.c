/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:47:59 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/05 10:04:39 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(t_info *arg)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = arg->philos;
	while (arg->dead == 0)
	{
		if (philos[i].m_count != -1 && \
		(get_time() - philos[i].last_meal) > arg->tt_die)
		{
			arg->dead = 1;
			pthread_mutex_lock(&arg->print_lock);
			printf("%lld %d  died\n", (get_time() - arg->start), philos[i].id);
			ft_usleep(200);
			return (NULL);
		}
		i++;
		if (i == arg->n_philo)
			i = 0;
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_message(" has taken a fork\n", philo->id, \
	&(philo->infos->print_lock), philo);
	pthread_mutex_lock(&(philo->fork_r));
	print_message(" has taken a fork\n", philo->id, \
	&(philo->infos->print_lock), philo);
	print_message(" is eating\n", philo->id, \
	&(philo->infos->print_lock), philo);
	philo->last_meal = get_time();
	philo->m_count++;
	ft_usleep(philo->infos->tt_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&(philo->fork_r));
}

int	check_meal_condition(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->meal_eaten));
	if (philo->m_count == philo->infos->eat_cond)
	{
		philo->infos->meals++;
		philo->m_count = -1;
		if (philo->infos->meals == philo->infos->n_philo)
		{
			philo->infos->dead = 1;
			pthread_mutex_lock(&philo->infos->print_lock);
			pthread_mutex_unlock(&(philo->infos->meal_eaten));
			return (1);
		}
		pthread_mutex_unlock(&(philo->infos->meal_eaten));
		return (1);
	}
	pthread_mutex_unlock(&(philo->infos->meal_eaten));
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
	{
		print_message(" is thinking\n", philo->id, \
		&(philo->infos->print_lock), philo);
		ft_usleep(30);
	}
	while (philo->infos->dead == 0)
	{
		eat(philo);
		if (check_meal_condition(philo))
			return (NULL);
		print_message(" is sleeping\n", philo->id, \
		&(philo->infos->print_lock), philo);
		ft_usleep(philo->infos->tt_sleep);
		print_message(" is thinking\n", philo->id, \
		&(philo->infos->print_lock), philo);
	}
	return (NULL);
}

void	start_simulation(t_info *info)
{
	int			i;
	pthread_t	tid[201];

	i = 0;
	info->start = get_time();
	while (i < info->n_philo)
	{
		info->philos[i].last_meal = info->start;
		if (pthread_create(&(tid[i]), NULL, &routine, &info->philos[i]) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < info->n_philo)
		pthread_detach(tid[i]);
	check_death(info);
}
