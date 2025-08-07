/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:57:17 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/07 20:30:51 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	mikrosaniye hassaslığında ölçülen zamanı milisaniyeye çevirmek için bir
	fonksiyon
*/
long long	get_time_ms(void)
{
	struct timeval	tv;
	long long	ms;
	
	if((gettimeofday(&tv, NULL)) == -1)
		return (-1);
	ms = (long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (ms);
}

/*
	Son yemek zamanından şimdiki zaman ne kadar geçmiş hesaplayan fonksiyon
	Umarım hesaplar
*/
long long	time_difference(t_philo *philo)
{
	long long	diff;
	long long	now;

	now =  get_time_ms();
	if (now == -1)
		return (-1);
	diff = now - (philo->eat_start);
	return (now);
}