/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:56 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/12 13:29:07 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* TODO Filozof sayısı 200'den fazla olmamalı, bunun kotrolünü yapan
	fonksiyonu yaz.
*/

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
 * Checks if the input contains only valid characters.
 * - Allowed: digits (0-9) and '-' sign (only at the beginning of a number).
 * - Invalid cases: "32-", "--3", "003", etc.
 */
static int	check_chars(char **el)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (el[i])
	{
		j = 0;
		while (el[i][j])
		{
			if ((el[i][j] != '-') && !ft_isdigit(el[i][j]) && (el[i][j] != '+'))
				return (0);
			else if ((el[i][0] == '-' && el[i][1] == '\0') || (el[i][0] == '+'
					&& el[i][1] == '\0'))
				return (0);
			else if ((j != 0 && el[i][j] == '-') || (j != 0 && el[i][j] == '+'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
 * A custom atoi function with integer limit checking.
 * - Returns 0 if the number exceeds int range.
 * - Handles negative numbers correctly.
 */
static int	modified_atoi_limits(char *str)
{
	int				i;
	int				sign;
	unsigned long	inte;

	i = 0;
	sign = 1;
	inte = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		inte = (inte * 10) + (str[i] - 48);
		i++;
		if (inte > 2147483647)
		{
			if (sign == 1)
				return (0);
		}
		else if (sign == -1 || inte == 0)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	inte;

	i = 0;
	sign = 1;
	inte = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		inte = (inte * 10) + (str[i] - 48);
		i++;
		if (inte > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return ((int)(inte * sign));
}

/*
	0 ve negatif sayı olmaz, integer değerlerini aşamaz
*/
int	validate_variables(char **argv)
{
	int	i;

	i = 0;
	if (!(check_chars(argv)))
		return (0);
	while (argv[i])
	{
		if (!(modified_atoi_limits(argv[i])))
			return (0);
		i++;
	}
	if (ft_atoi(argv[0]) > 200) //Filo sayısı 200'den fazla olamaz
		return (0);
	return (1);
}
