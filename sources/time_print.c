#include "philosophers.h"

#include "philosophers.h"

void print_state(t_philo *philo, t_type state)
{
    int stop;

    if (pthread_mutex_lock(&philo->table->print_state) != 0)
        return;

    pthread_mutex_lock(&philo->table->death_lock);
    stop = philo->table->stop_simulation;
    pthread_mutex_unlock(&philo->table->death_lock);

    if (state == DEAD)
    {
        // pthread_mutex_lock(&philo->table->print_state);
        printf("%ld Philo [%d] is dead\n", get_time() - philo->table->start, philo->id);
        pthread_mutex_unlock(&philo->table->print_state);
        return;
    }
    // f (!philo->table->stop_simulation)
    if (!stop)
    {
        if (state == THINKING)
            printf("%ld Philo [%d] is thinking\n", get_time() - philo->table->start, philo->id);
        else if (state == EATING)
            printf("%ld Philo [%d] is eating\n", get_time() - philo->table->start, philo->id);
        else if (state == SLEEPING)
            printf("%ld Philo [%d] is sleeping\n", get_time() - philo->table->start, philo->id);

        else if (state == FORK_TAKEN)
            printf("%ld Philo [%d] has taken fork\n", get_time() - philo->table->start, philo->id);
    }
    pthread_mutex_unlock(&philo->table->print_state);
}

void ft_usleep(long time, t_table *table)
{
    int a = 1;
    if (table)
        a++;
    long start;

    start = get_time();
    while (get_time() - start < time)
    {
        usleep(100);
    }
}

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
