/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:19:54 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/15 16:18:24 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_free(t_info *info)
{
	int	i;

	i = -1;
	while (!check_finish(&info->philos[0], 0))
		ft_sleep(10);
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

int	main(int ac, char **av)
{
	t_info	info;

	if (init(&info, ac, av))
		return (0);
	if (create_philos(&info))
		return (0);
	join_free(&info);
}
