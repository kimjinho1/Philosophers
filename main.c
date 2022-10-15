/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:19:54 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/15 18:47:20 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_free(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		pthread_join(info->philos[i].thread, NULL);
	free(info->philos);
	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_destroy(&info->forks[i]);
	free(info->forks);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->finish_mutex);
}

/*
void	destroy(t_info *info)
{
	int	i;
	int	yes;

	yes = 1;
	while (yes)
	{
		i = -1;
		while (++i < info->num_philo)
		{
			if (yes && check_dead(&info->philos[i]))
				yes = 0;
		}
		usleep(10);
	}
	join_free(info);
}
*/

void	destroy(t_info *info)
{
	int	i;
	int	yes;

	yes = 1;
	while (yes)
	{
		i = -1;
		info->num_full_philo = 0;
		while (++i < info->num_philo)
		{
			if (yes && check_dead(info, i))
				yes = 0;
		}
		usleep(10);
	}
	join_free(info);
}


int	main(int ac, char **av)
{
	t_info	info;

	if (init(&info, ac, av))
		return (0);
	if (create_philos(&info))
		return (0);
	destroy(&info);
}
