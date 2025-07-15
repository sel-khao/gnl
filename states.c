/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:14:32 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/15 15:10:43 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_pstats *p)
{
	put_message("is thinking...\n", p);
	ft_usleep(p->in->tthink);
}

void	sleeping(t_pstats *p)
{
	put_message("is sleeping ᶻ 𝗓 𐰁\n", p);
	ft_usleep(p->in->tsleep);
}

int	eating(t_pstats *p)
{
	int stop;

	f_lock(p);
	meal_update(p);
	put_message("started eating 𓐐𓎩\n", p);
	ft_usleep(p->in->teat);
	pthread_mutex_lock(p->meal_lock);
	p->eating = 0;
	stop = (p->in->nmeals > 0 && p->in->counter[p->id] >= p->in->nmeals);
	if (stop)
		p->full = 1;
	pthread_mutex_unlock(p->meal_lock);
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);
	return (stop);
}
/* 	if (p->in->counter[p->id] == p->in->nmeals)
	{
		pthread_mutex_lock(p->meal_lock);
		p->full = 1;
		pthread_mutex_unlock(p->meal_lock);
		return (1);
	}
	return (0);
} */

void	f_lock(t_pstats *p)
{	
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->lfork);
		put_message("has taken the left fork 𐂐\n", p);
		pthread_mutex_lock(p->rfork);
		put_message("has taken the right fork 𐂐\n", p);
	}
	else
	{
		pthread_mutex_lock(p->rfork);
		put_message("has taken the right fork 𐂐\n", p);
		pthread_mutex_lock(p->lfork);
		put_message("has taken the left fork 𐂐\n", p);
	}
}

void	meal_update(t_pstats *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->lastmeal = get_time();
	p->eating = 1;
	p->in->counter[p->id]++;
	pthread_mutex_unlock(p->meal_lock);
}
