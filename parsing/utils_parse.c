/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:12:11 by safamran          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:57 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	incorrect_number(char *str)
{
	int	a;

	if (!str)
		return (0);
	a = 0;
	if ((str[a] == '-' || str[a] == '+') && str[a + 1] == '\0')
		return (0);
	while (str[a] == '+' || str[a] == '-')
		a++;
	while (str[a] != '\0')
	{
		if (str[a] == '+' || str[a] == '-')
			return (0);
		if (str[a] < '0' || str[a] > '9')
			return (0);
		a++;
	}
	return (1);
}

int	parse_it(int argc, char *argv[], char **envp)
{
	int		a;
	long	n;

	(void)envp;
	a = argc - 1;
	while (a > 0)
	{
		n = ft_atol(argv[a]);
		if (incorrect_number(argv[a]) == 0)
			return (0);
		if (n > INT_MAX)
			return (1);
		if (argv[a][0] == '\0')
			return (2);
		if (a == 1 && n == 0)
			return (3);
		if (n < 0)
			return (4);
		a--;
	}
	return (-1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	result;

	result = 0;
	signe = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = signe * -1;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
	result = result * 10 + (nptr[i] - '0');
	i++;
	}
	return (signe * result);
}

long	ft_atol(char *str)
{
	long	result;
	long	signe;
	int		a;

	a = 0;
	signe = 1;
	result = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	while (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			signe = signe * -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		result = result * 10 + (str[a] - '0');
		a++;
	}
	return (result * signe);
}
