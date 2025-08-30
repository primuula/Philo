/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:51:55 by safamran          #+#    #+#             */
/*   Updated: 2025/08/29 15:02:26 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_cycle(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        ft_usleep(philo->table->time_to_eat / 2, philo->table);
    else if (philo->id == philo->table->nb_philo)
        ft_usleep(philo->table->time_to_eat / 4, philo->table);
    while (1)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        if (philo->table->stop_simulation)
        {
            pthread_mutex_unlock(&philo->table->death_lock);
            break;
        }
        pthread_mutex_unlock(&philo->table->death_lock);

        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (NULL);
}

void take_forks(t_philo *philo)
{
    if (philo->left < philo->right)
    {
        pthread_mutex_lock(philo->left);
        print_state(philo, FORK_TAKEN);
        pthread_mutex_lock(philo->right);
        print_state(philo, FORK_TAKEN);
    }

    else
    {
        pthread_mutex_lock(philo->right);
        print_state(philo, FORK_TAKEN);
        pthread_mutex_lock(philo->left);
        print_state(philo, FORK_TAKEN);
    }
}

void think(t_philo *philo)
{
    philo->state = THINKING;
    //pthread_mutex_lock(&philo->table->meal_lock);
    print_state(philo, THINKING);
    //pthread_mutex_unlock(&philo->table->meal_lock);
}

void eat(t_philo *philo)
{
    take_forks(philo);
    long start_eating;

    start_eating = get_time();
    // lock pour que le monitor lise les variable modife
    pthread_mutex_lock(&philo->table->meal_lock);
    philo->last_meal = start_eating;
    philo->nb_meals = philo->nb_meals + 1;
    // printf("DEBUG: Philo [%d] starts eating at %ld\n", philo->id, philo->last_meal);
    pthread_mutex_unlock(&philo->table->meal_lock);

    philo->state = EATING;
    //pthread_mutex_lock(&philo->table->meal_lock);
    print_state(philo, EATING);
    //pthread_mutex_unlock(&philo->table->meal_lock);

    ft_usleep(philo->table->time_to_eat, philo->table);

    pthread_mutex_unlock(philo->left);
    pthread_mutex_unlock(philo->right);
}

void philo_sleep(t_philo *philo)
{
    philo->state = SLEEPING;
    //pthread_mutex_lock(&philo->table->meal_lock);
    print_state(philo, SLEEPING);
    //pthread_mutex_unlock(&philo->table->meal_lock);
    ft_usleep(philo->table->time_to_sleep, philo->table);
}

/*
void    *philo_cycle(void *arg)
{
    t_philo *philo = (t_philo *)arg;

//    if (philo->id % 2 == 0)
//        ft_usleep(philo->table->time_to_eat / 2, philo->table);
//    else
//        ft_usleep(philo->table->time_to_eat, philo->table);

    while(!philo->table->stop_simulation)
    {
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (NULL);
}*/
/*
void    philo_cycle(t_table *table)
{
    int bool_eat;
    bool_eat = 0;

    // THINKING
    while (bool_eat == 0)
    {
        // EATING
        if (deux forks dispo)
        {
        last_meal = 0;
        bool_eat = 1;
        wait (time_to_eat);
        }
    }

    // SLEEPING
    if (bool_eat == 1)
    {
        bool_eat = 0;
        wait(time_to_sleep);
    }
}*/
