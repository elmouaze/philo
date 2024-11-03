/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:47:59 by ael-moua          #+#    #+#             */
/*   Updated: 2024/10/29 09:05:30 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign *= -1;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		if ((res > INT_MAX && sign == 1 ) \
			|| (res * -1  < INT_MIN  && sign == -1))
				return -1;
		str++;
	}
	while(*str == ' ')
		str++;
	if (*str != '\0')
		return -1;
	return ((int)res * sign);
}

void ft_parse(int ac, char **values,p_info *ph)
{
	ph->flag = 0;
	ph->philos_number = ft_atoi(values[1]);
	ph->tt_die = ft_atoi(values[2]);
	ph->tt_eat = ft_atoi(values[3]);
	ph->tt_sleep = ft_atoi(values[4]);
	ph->meals = 0;
	if (ph->philos < 0 || ph->tt_die  < 0
		|| ph->tt_eat < 0  || ph->tt_sleep < 0)
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