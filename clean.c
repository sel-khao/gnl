/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:07:11 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/15 14:32:56 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean_up(t_content *curr, t_lock *f, t_lock *m)
{
	int i;

	i = 0;
	while (i < curr->nphilos)
	{
		pthread_mutex_destroy(&f[i]);
		pthread_mutex_destroy(&m[i]);
		i++;
	}
	pthread_mutex_destroy(&curr->print);
	pthread_mutex_destroy(&curr->death_lock);
}
