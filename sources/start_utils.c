/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:52:00 by safamran          #+#    #+#             */
/*   Updated: 2025/09/02 14:00:33 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_single_philo(t_table *table)
{
	printf("0 Philo [1] has taken fork\n");
	ft_usleep(table->time_to_die, table);
	printf("%ld Philo [1] is dead\n", table->time_to_die);
	return (1);
}

int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].last_meal = table->start;
		if (pthread_create(&table->philos[i].thread, NULL, philo_cycle,
				&table->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	run_monitor(t_table *table)
{
	pthread_t	monitor_thread;

	ft_usleep(1, table);
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		return (0);
	pthread_join(monitor_thread, NULL);
	return (1);
}

void	join_all_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}
