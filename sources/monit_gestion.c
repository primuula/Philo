#include "philosophers.h"

void *monitor(void *arg)
{
    t_table *table = (t_table *)arg;

    while (!table->stop_simulation)
    {
        pthread_mutex_lock(&table->death_lock);
        if (table->stop_simulation)
        {
            pthread_mutex_unlock(&table->death_lock);
            break;
        }
        pthread_mutex_unlock(&table->death_lock);
        check_all_ate(table);
        ft_usleep(1, table);
    }
    return (NULL);
}

void check_all_ate(t_table *table)
{
    int all_ate = 1;
    int i = 0;

    while (i < table->nb_philo)
    {
        pthread_mutex_lock(&table->meal_lock);
        long time_since_meal = get_time() - table->philos[i].last_meal;
        if (time_since_meal > table->time_to_die)
        {
            pthread_mutex_unlock(&table->meal_lock);
            pthread_mutex_lock(&table->death_lock);
            table->stop_simulation = 1;
            pthread_mutex_unlock(&table->death_lock);
            print_state(&table->philos[i], DEAD);
            return;
        }
        if (table->nb_meals != -1 && table->philos[i].nb_meals < table->nb_meals)
            all_ate = 0;
        pthread_mutex_unlock(&table->meal_lock);
        i++;
    }
    if (all_ate && table->nb_meals != -1)
    {
        pthread_mutex_lock(&table->death_lock);
        table->stop_simulation = 1;
        pthread_mutex_unlock(&table->death_lock);
    }
}

void check_death(t_philo *philo)
{
    long time_since_meal;

    pthread_mutex_lock(&philo->table->meal_lock);
    time_since_meal = get_time() - philo->last_meal;
    pthread_mutex_unlock(&philo->table->meal_lock);

    if (time_since_meal > philo->table->time_to_die)
    {
        pthread_mutex_lock(&philo->table->death_lock);
        philo->table->stop_simulation = 1;
        pthread_mutex_unlock(&philo->table->death_lock);
        print_state(philo, DEAD);
    }
}
