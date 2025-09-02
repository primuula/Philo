/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:00:01 by safamran          #+#    #+#             */
/*   Updated: 2025/09/02 14:01:41 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, t_type state)
{
	int	stop;
	int	start;

	if (pthread_mutex_lock(&philo->table->print_state) != 0)
		return ;
	pthread_mutex_lock(&philo->table->death_lock);
	start = philo->table->start;
	stop = philo->table->stop_simulation;
	pthread_mutex_unlock(&philo->table->death_lock);
	if (state == DEAD)
	{
		printf("%ld Philo [%d] is dead\n",
			get_time() - philo->table->start, philo->id);
		pthread_mutex_unlock(&philo->table->print_state);
		return ;
	}
	if (!stop)
		state_print(philo, state);
	pthread_mutex_unlock(&philo->table->print_state);
}

void	state_print(t_philo *philo, t_type state)
{
	if (state == THINKING)
		printf("%ld %d is thinking\n",
			get_time() - philo->table->start, philo->id);
	else if (state == EATING)
		printf("%ld %d is eating\n",
			get_time() - philo->table->start, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n",
			get_time() - philo->table->start, philo->id);
	else if (state == FORK_TAKEN)
		printf("%ld %d has taken fork\n",
			get_time() - philo->table->start, philo->id);
}

void	ft_usleep(long time, t_table *table)
{
	long	start;
	int		a;

	a = 1;
	if (table)
		a++;
	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->stop_simulation)
		{
			pthread_mutex_unlock(&table->death_lock);
			return ;
		}
		pthread_mutex_unlock(&table->death_lock);
		usleep(100);
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
