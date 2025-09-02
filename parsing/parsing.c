/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:18:39 by safamran          #+#    #+#             */
/*   Updated: 2025/09/02 14:58:57 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc != 6 && argc != 5)
		return (printf("Incorrect number of argument\n"), 0);
	if (parse_it(argc, argv, envp) == 0)
		return (printf("Incorrect number\n"), 0);
	if (parse_it(argc, argv, envp) == 1)
		return (printf("Number out of limits\n"), 0);
	if (parse_it(argc, argv, envp) == 2)
		return (printf("Incorrect number \n"), 0);
	if (parse_it(argc, argv, envp) == 3)
		return (printf("One philosopher is needed at least !\n"), 0);
	if (parse_it(argc, argv, envp) == 4)
		return (printf("Negative number\n"), 0);
	if (argv[5] && argv[5][0] == '0')
		return (printf("No meals today. The philosophers remain hungry...\n"));
	if (atoi(argv[1]) > 200)
		return (printf("Too many philosophers !\n"));
	return (-1);
}
