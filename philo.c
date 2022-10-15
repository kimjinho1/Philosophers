/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:39:50 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/15 18:48:38 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->eat_mutex);
	if ((get_time() - philo->last_eat_time) >= philo->info->time_to_die)
	{
		print_status(philo, "died");
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return (1);
	}
	else if (philo->info->num_must_eat > 0 && philo->eat_cnt >= \
			philo->info->num_must_eat)
	{
		philo->info->num_full_philo++;
		if (philo->info->num_full_philo >= philo->info->num_philo)
			check_finish(philo, 1);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->eat_mutex);
	return (0);
}
*/

int	check_dead(t_info *info, int i)
{
	pthread_mutex_lock(&info->eat_mutex);
	if ((get_time() - info->philos[i].last_eat_time) >= info->time_to_die)
	{
		print_status(&info->philos[i], "died");
		check_finish(&info->philos[i], 1);
		pthread_mutex_unlock(&info->eat_mutex);
		return (1);
	}
	else if (info->num_must_eat > 0 && info->philos[i].eat_cnt >= \
				info->num_must_eat)
	{
		info->num_full_philo += 1;
		//printf("full_cnt: %d\n", info->num_full_philo);
		if (info->num_full_philo >= info->num_philo)
		{
			check_finish(&info->philos[i], 1);
			pthread_mutex_unlock(&info->eat_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&info->eat_mutex);
	return (0);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->eat_cnt += 1;
	pthread_mutex_unlock(&philo->info->eat_mutex);
	ft_sleep(philo, philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->info->eat_mutex);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
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

void	*philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat);
	while (42)
	{
		if (check_finish(philo, 0))
			return (0);
		eat(philo);
		print_status(philo, "is sleeping");
		ft_sleep(philo, philo->info->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (0);
}
