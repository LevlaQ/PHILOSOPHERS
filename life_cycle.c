/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:28 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 09:01:05 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*waitress_glaring(void	*philo)
{
	(void)philo;
	printf("Waitress is lusting after blood :D\n");
	return (NULL);
}

void	*philo_life_cycle(void *philo) 
{
	(void)philo;
	printf("Philo living its best life!\n");
	return (NULL);
}