/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:18:34 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/17 09:18:36 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	close_info(t_info *info)
{
	int		i;
	int		stat;

	i = -1;
	while (++i < info->num_philo)
	{
		waitpid(-1, &stat, 0);
		if (stat != 0)
		{
			i = -1;
			while (++i < info->num_philo)
				kill(info->philos[i].pid, SIGTERM);
			break ;
		}
	}
	free(info->philos);
	sem_close(info->forks);
	sem_close(info->eat_sem);
	sem_close(info->print_sem);
}

int	main(int ac, char **av)
{
	t_info		info;

	if (init_info(&info, ac, av))
		return (0);
	if (init_philos(&info))
	{
		free(info.philos);
		return (0);
	}
	fork_philos(&info);
	close_info(&info);
}
