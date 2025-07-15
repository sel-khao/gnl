/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:11:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/14 09:11:00 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

#define RED "\033[1;31m"
#define RESET "\033[0m"

typedef pthread_mutex_t		t_lock;
typedef struct timeval		t_timeval;

typedef struct s_content
{
	size_t			teat;
	int				full;
	size_t			tdie;
	int				death;
	size_t			start;
	pthread_mutex_t	print;
	size_t			tsleep;
	int				nmeals;
	int				tthink;
	pthread_t		monitor;
	int				nphilos;
	pthread_mutex_t	death_lock;
	int				counter[250];
}	t_content;

typedef struct s_pstats
{
	int				id;
	t_content		*in;
	int				full;
	int				turn;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	int				tthink;
	pthread_t		thread;
	int				eating;
	size_t			lastmeal;
	pthread_mutex_t	*meal_lock;
}	t_pstats;

long long	get_time(void);
void		error(int code);
int			eating(t_pstats *p);
int			checkarg(char *str);
void		*routine(void *arg);
void		f_lock(t_pstats *p);
void		thinking(t_pstats *p);
void		sleeping(t_pstats *p);
void		*monitoring(void *arg);
void		ft_usleep(long long ms);
long		ft_atoi(const char *str);
void		put_time(t_content curr);
int			is_alive(t_content *curr);
void		meal_update(t_pstats *p);
int			check_args(int ac, char *av[]);
void		put_dead(t_content *curr, int i);
void		put_message(char *s, t_pstats *p);
int			end_death(t_pstats *p, t_content *curr);
void		clean_up(t_content *curr, t_lock *f, t_lock *m);
int			check_full(t_pstats *p, t_content *curr);
int			init_thrds(t_pstats *p, t_content *curr);
void		init_content(t_content *it, int ac, char **av);
void		init_mtx(t_lock *f, t_lock *m, t_content *curr);
void		init_pstats(t_pstats *p, t_lock *m, t_content *curr, t_lock *f );

#endif
