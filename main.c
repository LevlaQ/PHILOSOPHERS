/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:03:07 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 13:44:52 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	TODO Tek filozof için de bir koşul, durum oluşturulmalı
*/

static int	error_main(int argc, char **argv)
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
	Bütün değişkenlerin error'dan düzgün bir şekilde geçerse masayı donatma işini
	yap
	Dinamik array açtım, t_philo tipi data yapısını tutacak. Her filozof 
	kendi array'inde çalışacak sadece çatallar (mutex kilitler) ortak olacak

	TODO unsigned long long cinsinden mikrosaniyeden milisanye hesabı yap
*/
int	main(int argc, char **argv)
{
	t_philo_table	table;
	t_philo			philo[MAX];
	mtx				forks[MAX];
	
	if (!(error_main(argc, argv + 1)))
		return (1);
	fill_structs(philo, argv + 1, forks, &table); //Program argümanını vermiyorum
	initiliazing_mutexes(&table, forks);
	//test_print_philos(philo, ft_atoi(argv[1])); //TEST
	printf("PHILO AT WORK\n");
	return (0);
}
