/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:18:29 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/17 09:18:31 by jinhokim         ###   ########.fr       */
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

static sem_t	*init_sem(const char *name, unsigned int n)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644, n);
	sem_unlink(name);
	return (sem);
}

int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philos)
		return (print_error("Error: init_philos malloc\n"));
	info->forks = init_sem("forks", info->num_philo);
	info->eat_sem = init_sem("eat", 1);
	info->print_sem = init_sem("print", 1);
	if (info->forks == SEM_FAILED || info->eat_sem == SEM_FAILED || \
			info->print_sem == SEM_FAILED)
		return (print_error("Error: sem_open\n"));
	while (++i < info->num_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].info = info;
	}
	return (0);
}

void	fork_philos(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time();
	while (++i < info->num_philo)
	{
		info->philos[i].last_eat_time = info->start_time;
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			philo_start(&info->philos[i]);
		else if (info->philos[i].pid < 0)
			exit(print_error("Error: fork fail\n"));
	}
}
