/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:39:50 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/15 16:16:27 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	act(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->last_eat_time = get_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->info->eat_mutex);
	ft_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "is sleeping");
	ft_sleep(philo->info->time_to_sleep);
	print_status(philo, "is thinking");
}

int	check_finish(t_philo *philo, int yes)
{
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (yes)
	{
		philo->info->finish = 1;
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	if (philo->info->finish)
	{
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->finish_mutex);
	return (0);
}

void	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->eat_mutex);
	if ((get_time() - philo->last_eat_time) >= philo->info->time_to_die)
	{
		print_status(philo, "died");
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return ;
	}
	else if (philo->info->num_must_eat > 0 && philo->eat_cnt >= \
			philo->info->num_must_eat)
	{
		philo->info->num_full_philo++;
		if (philo->info->num_full_philo >= philo->info->num_philo)
			check_finish(philo, 1);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->eat_mutex);
	return ;
}

void	*philo_start(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat);
	while (42)
	{
		if (check_finish(philo, 0))
			return (0);
		i = -1;
		while (++i < philo->info->num_philo)
			check_dead(philo);
		act(philo);
	}
	return (0);
}
