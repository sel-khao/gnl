/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:41:04 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/15 15:40:09 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	t_timeval	tv;
	long long	timelaps;

	if (gettimeofday(&tv, NULL))
	{
		printf("gettimeofday failed\n");
		exit(1);
	}
	timelaps = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timelaps);
}

int	end_death(t_pstats *p, t_content *curr)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_time();
	while (i < curr->nphilos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (time - p[i].lastmeal >= curr->tdie)
		{
			pthread_mutex_unlock(p[i].meal_lock);
			pthread_mutex_lock(&curr->death_lock);
			if (curr->death == 0)
			{
				curr->death = 1;
				pthread_mutex_lock(&curr->print);
				put_time(*curr);
				printf("philosopher %d died :c\n", p[i].id);
				pthread_mutex_unlock(&curr->print);
			}
			pthread_mutex_unlock(&curr->death_lock);
			return (1);
		}
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_pstats	*p;
	t_content	*curr;

	p = (t_pstats *)arg;
	curr = p->in;
	while (is_alive(p->in))
	{
		if (check_full(p, curr))
			break ;
		if (end_death(p, curr))
			break ;
		ft_usleep(1);
	}
	return	(NULL);
}

int	is_alive(t_content *curr)
{
	pthread_mutex_lock(&curr->death_lock);
	if (curr->death == 1)
		return (pthread_mutex_unlock(&curr->death_lock), 0);
	pthread_mutex_unlock(&curr->death_lock);
	return (1);
}

void	*routine(void *arg)
{
	t_pstats	*p;
	t_content	*curr;

	p = (t_pstats *)arg;
	curr = p->in;
	if (curr->nphilos == 1)
	{
		ft_usleep(curr->tdie);
		return (NULL);
	}
	if (p->id % 2 == 0)
		ft_usleep(curr->tthink / 10);
	while (is_alive(curr))
	{
		if (eating(p))
			break ;
		sleeping(p);
		thinking(p);
	}
	return (NULL);
}


