/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcitons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:06:06 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 08:26:46 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Simülasyonun herhangi bir aşamasında serbest bırakma işlemlerini yapmalı
	hata durumlarında da bütün alanlar doldurulmamışsa bile çıkışı sağlamalı.
	Böyle bir fonksiyon yaz.
*/
void	finish_simulation(t_philo_table *table, mtx *forks)
{
	(void)table;
	(void)forks;
	printf("BE FREE!\n");
}