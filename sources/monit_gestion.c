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
/*
void check_all_ate(t_table *table)
{
    int all_ate;
    int i;
    all_ate = 1;
    i = 0;

    while (i < table->nb_philo)
    {
        pthread_mutex_lock(&table->meal_lock);
        check_death(&table->philos[i]);
        if (table->nb_meals != -1 && (table->philos[i].nb_meals < table->nb_meals))
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
}*/

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

/*
void   check_death(t_philo *philo)
{

    if (get_time() - philo->last_meal > philo->table->time_to_die)
    {
        philo->table->stop_simulation = 1;
        print_state(philo, DEAD);
    }
}

void check_all_ate(t_table *table)
{
    int all_ate;
    int i;
    all_ate = 1;
    int meals_eaten;
    i = 0;

    while (i < table->nb_philo)
    {
        pthread_mutex_lock(&table->philos[i].table->meal_lock);
        check_death(&table->philos[i]);

        if (table->nb_meals != -1)
        {
            meals_eaten = table->philos->nb_meals;
            if (meals_eaten < table->nb_meals)
                all_ate = 0;
        }

        // if (table->nb_meals != -1 && (table->philos[i].nb_meals < table->nb_meals))
        //     all_ate = 0;
        pthread_mutex_unlock(&table->philos[i].table->meal_lock);
        i++;
    }

    if (all_ate && table->nb_meals != -1)
    {
        pthread_mutex_lock(&table->death_lock);
        table->stop_simulation = 1;
        pthread_mutex_unlock(&table->death_lock);
    }
}

void    *monitor(void *arg)
{
    int all_ate;
    int i;
    t_table *table = (t_table *)arg;
    i = 0;
    while(!table->stop_simulation)
    {
            all_ate = 1;
            i = 0;
        all_ate = 1;
        while (i < table->nb_philo)
        {
            //pthread_mutex_lock
            pthread_mutex_lock(&table->meal_lock);
            check_death(&table->philos[i]);
            if (table->nb_meals != -1 && (table->philos[i].nb_meals < table->nb_meals))
                all_ate = 0;
            pthread_mutex_unlock(&table->meal_lock);
            i++;
        }

        if (all_ate)
        {
            table->stop_simulation = 1;
            //return (NULL);
        }
        ft_usleep(1, table);
    }
    return (NULL);
}

void   check_death(t_philo *philo)
{
    if (get_time() - philo->table->philos->last_meal > philo->table->time_to_die)
    {
        philo->table->stop_simulation = 1;
        print_state(philo, DEAD);
    }
}


*/
