/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:04:20 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/14 09:04:20 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_content(t_content *it, int ac, char **av)
{
	int	i;

	i = 0;
	it->nphilos = ft_atoi(av[1]);
	it->tdie = ft_atoi(av[2]);
	it->teat = ft_atoi(av[3]);
	it->tsleep = ft_atoi(av[4]);
	it->full = 0;
	it->death = 0;
	it->start = get_time();
	if (ac == 5)
		it->nmeals = -1;
	else if (ac == 6)
		it->nmeals = ft_atoi(av[5]);
	while (i <= it->nphilos)
		it->counter[i++] = 0;
}

void	init_pstats(t_pstats *p, t_lock *m, t_content *curr, t_lock *f )
{
	int i = 0;
	if (curr->tdie < 100 && curr->teat < 100)
		curr->tthink = 5;
	else
		curr->tthink = 20;
	while (i < curr->nphilos)
	{
		p[i].id = i + 1;
		p[i].lastmeal = get_time();
		p[i].eating = 0;
		p[i].full = 0;
		p[i].turn = 0;
		p[i].meal_lock = &m[i];
		p[i].in = curr;
		p[i].lfork = &f[i];
		p[i].rfork = &f[(i + 1) % curr->nphilos];
		i++;
	}
}

void	init_mtx(t_lock *f, t_lock *m, t_content *curr)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&curr->print, NULL))
		error(4);
	if (pthread_mutex_init(&curr->death_lock, NULL))
		error(4);
	while (i < curr->nphilos)
	{
		if (pthread_mutex_init(&f[i], NULL))
			error(4);
		if (pthread_mutex_init(&m[i], NULL))
			error(4);
		i++;
	}
}

int	init_thrds(t_pstats *p, t_content *curr)
{
	int	i;

	i = 0;
	if (pthread_create(&curr->monitor, NULL, monitoring, p))
		error(5);
	while (i < curr->nphilos)
	{
		if (pthread_create(&p[i].thread, NULL, routine, &p[i]))
			error(5);
		i++;
	}
	return (1);
}
