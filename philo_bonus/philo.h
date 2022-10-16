/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:59:17 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/17 07:54:23 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	long long		last_eat_time;
	pid_t			pid;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				finish;
	long long		start_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*eat_sem;
}					t_info;

int			print_error(char *message);
int			ft_atoi(const char *nptr);
long long	get_time(void);
void		print_status(t_philo *philo, const char *message);
void		ft_sleep(long long ms);

int			init_info(t_info *info, int ac, char **av);
int			init_philos(t_info *info);
void		fork_philos(t_info *info);

void		*check_dead(void *arg);
void		philo_start(t_philo *philo);

#endif
