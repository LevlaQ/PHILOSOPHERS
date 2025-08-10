/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:28 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 13:36:07 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Bir şekilde supervisor'ın kendi rutinin başlangıcı olacak olan gonksiyon olacak
*/
void	*waitress_glaring(void	*philo)
{
	(void)philo;
	printf("Waitress is lusting after blood :D\n");
	return (NULL);
}

/*
	Filo yaşam döngüsü algoritması fonksiyonu
*/
void	*philo_life_cycle(void *philo) 
{
	(void)philo;
	printf("Philo living its best life!\n");
	return (NULL);
}