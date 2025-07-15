/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:04:34 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/15 14:32:48 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{	
	if (ac >= 2)
	{
		int			i;
		t_content	curr;
		t_lock		f[200];
		t_lock		m[200];
		t_pstats	p[200];
		check_args(ac, av);
		init_content(&curr, ac, av);
		init_mtx(f, m, &curr);
		init_pstats(p, m, &curr, f);
		init_thrds(p, &curr);
		i = 0;
		while (i < curr.nphilos)
		{
			pthread_join(p[i].thread, NULL);
			i++;
		}
		pthread_join(curr.monitor, NULL);
		clean_up(&curr, f, m);
	}
	return (0);
}
