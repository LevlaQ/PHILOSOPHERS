/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:44:33 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/07 18:28:06 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_main(int argc, char **argv)
{
	if (!(argc >= 5 && argc <= 6))
	{
		printf("ERROR: Invalid argument count!\n");
		return (0);
	}
	if (!(validate_variables(argv)))
	{
		printf("ERROR: Invalid numbers!\n");
		return (0);
	}
	return (1);
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
	return (1);
}