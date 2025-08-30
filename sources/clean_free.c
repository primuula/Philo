#include "philosophers.h"

void free_forks_mutex(t_table *table, int i)
{
    int n;

    n = 0;
    while (n < i)
    {
        pthread_mutex_destroy(&table->forks[n]);
        n++;
    }
    free(table->forks);
}

void free_all_mutexes(t_table *table)
{
    free_forks_mutex(table, table->nb_philo);
    pthread_mutex_destroy(&table->print_state);
    pthread_mutex_destroy(&table->meal_lock);
    pthread_mutex_destroy(&table->death_lock);
}

// cas 1 philo pas a gerer check sujet

// start simule pour le cas d un philo