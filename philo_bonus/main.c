/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:57:39 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/16 17:47:59 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (init_info(&info, ac, av))
		return (0);
	if (init_philos(&info))
		return (free_info(&info));
	if (init_mutex(&info))
		return (free_destroy(&info));
	if (create_philos(&info))
		return (0);
	destroy(&info);
}
