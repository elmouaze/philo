/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:41:54 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/07 20:44:50 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '\0' || *str == '-')
		return (-1);
	if (*str == '+')
		str++;
	if (*str == '\0' || (*str >= 9 && *str <= 13) || *str == ' ')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		if (res > INT_MAX)
			return (-1);
		str++;
	}
	while (*str == ' ')
		str++;
	if (*str != '\0')
		return (-1);
	return ((int)res * sign);
}

void	ft_parse(int ac, char **values, t_info *ph)
{
	ph->flag = 0;
	ph->n_philo = ft_atoi(values[1]);
	ph->tt_die = ft_atoi(values[2]);
	ph->tt_eat = ft_atoi(values[3]);
	ph->tt_sleep = ft_atoi(values[4]);
	ph->meals = 0;
	if (ph->philos < 0 || ph->tt_die < 0 \
		|| ph->tt_eat < 0 || ph->tt_sleep < 0 || ph->n_philo <= 0)
		ph->flag = -1;
	if (ac == 6)
	{
		ph->eat_cond = ft_atoi(values[5]);
		if (ph ->eat_cond < 0)
			ph->flag = -1;
	}
	else
		ph->eat_cond = -1;
	ph->dead = 0;
	ph->meals = 0;
}

int	init_mutexes(t_info *info)
{
	if (pthread_mutex_init(&(info->dead_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(info->meal_eaten), NULL) != 0)
		return (destroy_mutex(info, 1), 1);
	if (pthread_mutex_init(&(info->print_lock), NULL) != 0)
		return (destroy_mutex(info, 2), 1);
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	if (init_mutexes(info))
		return (1);
	info->philos = malloc (sizeof(t_philo) * info->n_philo);
	if (!info->philos)
		return (destroy_mutex(info, 3), 1);
	while (i < info->n_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].m_count = 0;
		info->philos[i].infos = info;
		info->meals = 0;
		if (pthread_mutex_init(&(info->philos[i].fork_r), NULL) != 0)
			return (destroy_all(info, i), 1);
		if (i + 1 == info->n_philo)
			info->philos[i].fork_l = &(info->philos[0].fork_r);
		else
			info->philos[i].fork_l = &(info->philos[i + 1].fork_r);
		i++;
	}
	return (start_simulation(info), 0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
		return (printf("error in arguments"), 1);
	ft_parse(ac, av, &info);
	if (info.flag == -1)
		return (printf("error in arguments"), 1);
	if (info.eat_cond == 0)
		return (0);
	if (info.n_philo > 200)
		return (printf("Do not test with more than 200 \
philosophers.\n"), 1);
	if (init_philo(&info))
		return (1);
	destroy_all(&info, info.n_philo);
	return (0);
}
