/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:51:55 by safamran          #+#    #+#             */
/*   Updated: 2025/08/29 17:23:47 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_table(t_table *table)
{
    printf("Nombre de philo = %d\n", table->nb_philo);
    printf("Time to die     = %ld\n", table->time_to_die);
    printf("Time to eat     = %ld\n", table->time_to_eat);
    printf("Time to sleep   = %ld\n", table->time_to_sleep);
    if (table->nb_meals == -1)
        printf("\n*pas de nb_meals preciser*\n");
    else
        printf("nb_meals        = %d\n", table->nb_meals);
}
int main(int argc, char **argv, char **envp)
{
    t_table *table;
    table = malloc(sizeof(t_table) * 1);
    if (!table)
        return (1);

    if (parsing(argc, argv, envp) != -1)
        return (free(table), 0);
    if (init_table(argc, argv, envp, table) == 0)
        return (printf("init error\n"), free(table), 1);
    else
    {
        // print_table(table);
        start_simulation(table);
        free_all_mutexes(table);
        free(table->philos);
        free(table);
    }
    return (0);
}