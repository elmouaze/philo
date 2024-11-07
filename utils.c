/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:56:08 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/05 10:34:26 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, int id, \
pthread_mutex_t *print_lock, t_philo *arg)
{
	pthread_mutex_lock(print_lock);
	if (arg->infos->dead != 1)
		printf("%lld %d %s", (get_time() - arg->infos->start), id, str);
	pthread_mutex_unlock(print_lock);
}

long long	get_time(void)
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

void	destroy_mutex(t_info *info, int count)
{
	pthread_mutex_destroy(&info->dead_lock);
	if (count > 1)
		pthread_mutex_destroy(&info->meal_eaten);
	if (count > 2)
		pthread_mutex_destroy(&info->print_lock);
}

void	destroy_all(t_info *info, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_destroy(&info->philos[i].fork_r);
	destroy_mutex(info, 3);
	free(info->philos);
}
