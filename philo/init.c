/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:59:22 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/16 18:03:34 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info, int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (print_error("Error: argc it not 5, 6\n"));
	info->num_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (info->num_philo < 1 || info->time_to_die < 1 || \
			info->time_to_eat < 1 || info->time_to_sleep < 1)
		return (print_error("Error: wrong input\n"));
	if (ac == 6)
	{
		info->num_must_eat = ft_atoi(av[5]);
		if (info->num_must_eat < 1)
			return (print_error("Error: wrong input\n"));
	}
	else
		info->num_must_eat = -1;
	info->finish = 0;
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	info->start_time = get_time();
	if (!info->philos || !info->forks)
		return (print_error("Error: init_philos malloc\n"));
	while (++i < info->num_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->num_philo;
		info->philos[i].eat_cnt = 0;
		info->philos[i].last_eat_time = info->start_time;
		info->philos[i].info = info;
	}
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (print_error("Error: forks mutex_init\n"));
	}
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (print_error("Error: print mutex_init\n"));
	if (pthread_mutex_init(&info->eat_mutex, NULL))
		return (print_error("Error: eat mutex_init\n"));
	if (pthread_mutex_init(&info->finish_mutex, NULL))
		return (print_error("Error: finish mutex_init\n"));
	return (0);
}

int	create_philos(t_info *info)
{
	int	i;

	i = -1;
	if (info->num_philo == 1)
	{
		print_status(&info->philos[0], "has taken a fork");
		ft_sleep(&info->philos[0], info->time_to_die);
		print_status(&info->philos[0], "died");
		check_finish(&info->philos[0], 1);
		return (0);
	}
	while (++i < info->num_philo)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_start, \
			&(info->philos[i])))
			return (print_error("Error: philos thread create\n"));
	}
	return (0);
}
