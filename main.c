/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:03:07 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/07 18:49:39 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Bütün değişkenlerin error'dan düzgün bir şekilde geçerse masayı donatma işini
	yap
	Dinamik array açtım, t_philo tipi data yapısını tutacak. Her filozof 
	kendi array'inde çalışacak sadece çatallar (mutex kilitler) ortak olacak

	TODO unsigned long long cinsinden mikrosaniyeden milisanye hesabı yap
*/
int	main(int argc, char **argv)
{
	t_philo	*philo;
	
	if(!(error_main(argc, argv + 1)))
		return (0);//FIXME Dönüş değeri
	philo = ft_calloc(ft_atoi(argv[1]) + 1, sizeof(t_philo)); //MALLOC
	//if (!philo)
		/* Bütün malloc ile yapılan yapıyı serbest bırakacak fonksiyon, yapı tamamlanınca yazacağım*/
	fill_structs_main(philo, argv + 1); //Program argümanını vermiyorum
	//test_print_philos(philo, ft_atoi(argv[1])); //TEST
	printf("PHILO AT WORK\n");
	return (0);
}