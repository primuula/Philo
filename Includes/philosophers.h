/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/02 16:59:58 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// shakuyaku

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_type
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	FORK_TAKEN,
}	t_type;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	pthread_t		thread;
	t_type			state;
	int				nb_meals;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			start;
	int				nb_philo;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_state;
	pthread_mutex_t	death_lock;
	int				nb_meals;
	int				stop_simulation;
}	t_table;

/* ********* sources ************* */
int		main(int argc, char *argv[], char **envp);
int		init_table(int argc, char **argv, char **envp, t_table *table);
int		init_mutex(t_table *table);
int		init_philo(t_table *table);
int		start_simulation(t_table *table);
int		handle_single_philo(t_table *table);
int		create_philo_threads(t_table *table);
int		run_monitor(t_table *table);
void	join_all_threads(t_table *table);
void	check_all_ate(t_table *table);

/* ********* parsing ********** */
int		parsing(int argc, char **argv, char **envp);
int		parse_it(int argc, char **argv, char **envp);
int		incorrect_number(char *str);
long	ft_atol(char *str);
int		ft_atoi(const char *nptr);

/* *******  cycle  ******* */
void	*philo_cycle(void *arg);
void	*monitor(void *arg);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

/* *******  time/print utils  ******* */
void	print_state(t_philo *philo, t_type state);
void	ft_usleep(long time, t_table *table);
long	get_time(void);
void	state_print(t_philo *philo, t_type state);

/* ***** cleanup function ***** */
void	free_forks_mutex(t_table *table, int i);
void	free_all_mutexes(t_table *table);
void	print_table(t_table *table);

/* ********   monitor   ********* */
void	*monitor(void *arg);
void	check_death(t_philo *philo);
void	racc(t_table *table, int i, int time_since_meal);
void	check_philo(t_table *table, int i, int *all_ate);

#endif
