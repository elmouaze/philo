/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:56:08 by ael-moua          #+#    #+#             */
/*   Updated: 2024/10/26 03:12:32 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

void	print_message(char *str, int id, pthread_mutex_t *print_lock,long long start,t_philo *arg)
{
	pthread_mutex_lock(&arg->infos->dead_lock);
	if (arg->infos->dead == -1)
	{
		pthread_mutex_unlock(&arg->infos->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&arg->infos->dead_lock);
	pthread_mutex_lock(print_lock);
	printf("%lld %d %s", get_time() - start ,id, str);
	pthread_mutex_unlock(print_lock);
}

long long get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(10);
	return (0);
}
