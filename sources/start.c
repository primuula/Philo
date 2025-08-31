#include "philosophers.h"

#include "philosophers.h"

int init_table(int argc, char **argv, char **envp, t_table *table)
{
    (void)envp;

    table->nb_philo = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->nb_meals = ft_atol(argv[5]);
    else
        table->nb_meals = -1;

    table->stop_simulation = 0;

    table->start = get_time();
    if (init_mutex(table) == 0)
        return (0);
    if (init_philo(table) == 0)
        return (0);

    return (1);
}

int init_philo(t_table *table)
{
    table->philos = malloc(sizeof(t_philo) * table->nb_philo);
    if (!table->philos)
        return (0);
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].last_meal = table->start;
        table->philos[i].state = THINKING;
        table->philos[i].nb_meals = 0;
        table->philos[i].table = table;
        table->philos[i].left = &table->forks[i];
        table->philos[i].right = &table->forks[(i + 1) % table->nb_philo];
        i++;
    }
    return (1);
}

int init_mutex(t_table *table)
{
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
    if (!table->forks)
        return (0);
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            return (free_forks_mutex(table, i), 0);
        i++;
    }
    if (pthread_mutex_init(&table->print_state, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&table->death_lock, NULL) != 0)
        return (0);
    return (1);
}

int start_simulation(t_table *table)
{

    if (table->nb_philo == 1)
        return (handle_single_philo(table));

    if (create_philo_threads(table) == 0)
        return (0);

    if (run_monitor(table) == 0)
        return (0);

    join_all_threads(table);
    return (1);
}
