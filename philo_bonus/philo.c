/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:59:28 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/16 22:36:09 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_eat_finish(void *arg)
{
	int		i;
	t_info	*info;

	i = -1;
	info = arg;
	while (++i < info->num_philo)
		sem_wait(info->full_finish_sem);
	sem_post(info->finish_sem);
	print_status(&info->philos[0], "f");
	return (NULL);
}

void	*check_finish(void *arg)
{
	int		i;
	t_info	*info;

	i = -1;
	info = arg;
	sem_wait(info->finish_sem);
	while (++i < info->num_philo)
		kill(info->philos[i].pid, SIGKILL);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	ft_sleep(philo->info->time_to_eat);
	sem_wait(philo->info->eat_sem);
	philo->eat_cnt += 1;
	philo->last_eat_time = get_time();
	sem_post(philo->info->eat_sem);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	*check_dead(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (42)
	{
		sem_wait(philo->info->eat_sem);
		if ((get_time() - philo->last_eat_time) >= philo->info->time_to_die)
		{
			print_status(philo, "died");
			sem_post(philo->info->eat_sem);
			sem_post(philo->info->finish_sem);
			return (NULL);
		}
		if (philo->info->num_must_eat > 0 && philo->eat_cnt >= \
				philo->info->num_must_eat)
		{
			sem_post(philo->info->eat_sem);
			sem_wait(philo->info->full_finish_sem);
			return (NULL);
		}
		sem_post(philo->info->eat_sem);
	}
	return (NULL);
}

void	philo_start(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_dead, philo);
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	while (42)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		ft_sleep(philo->info->time_to_sleep);
		print_status(philo, "is thinking");
	}
	exit(0);
}
