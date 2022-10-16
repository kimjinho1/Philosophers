/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:57:39 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/16 22:17:04 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_info(t_info *info)
{
	free(info->philos);
	free(info->forks);
	return (0);
}

static void	close_info(t_info *info)
{
	int		i;
	int		stat;

	i = -1;
	while (++i < info->num_philo)
		waitpid(info->philos[i].pid, &stat, 0);
	free(info->philos);
	sem_close(info->forks);
	sem_close(info->eat_sem);
	sem_close(info->print_sem);
	sem_close(info->finish_sem);
	printf("check1\n");
	sem_close(info->full_finish_sem);
	printf("check2\n");
}

int	main(int ac, char **av)
{
	t_info		info;
	pthread_t	thread;

	if (init_info(&info, ac, av))
		return (0);
	if (init_philos(&info))
		return (free_info(&info));
	fork_philos(&info);
	if (info.num_must_eat > 0)
		pthread_create(&thread, NULL, check_eat_finish, &info);
	pthread_create(&thread, NULL, check_finish, &info);
	close_info(&info);
}
