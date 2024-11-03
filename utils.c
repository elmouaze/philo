/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:56:08 by ael-moua          #+#    #+#             */
/*   Updated: 2024/10/29 08:45:24 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

void	print_message(char *str, int id, pthread_mutex_t *print_lock,t_philo *arg)
{
	if (!get_death_status(arg->infos))
		return ;
	pthread_mutex_lock(print_lock);
	printf("%lld %d %s", (get_time() - arg->start) ,id, str);
	pthread_mutex_unlock(print_lock);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t t_ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < t_ms)
		usleep(100);
}