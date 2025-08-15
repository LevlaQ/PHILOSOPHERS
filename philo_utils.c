/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:57:17 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/15 12:40:15 by gyildiz          ###   ########.fr       */
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
	FIXME
	Son yemek zamanından şimdiki zaman ne kadar geçmiş hesaplayan fonksiyon
	Umarım hesaplar
*/
long long	time_difference(t_philo *philo)
{
	long long	diff;

	pthread_mutex_lock(philo->last_meal_lock);
	diff = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(philo->last_meal_lock);
	return (diff);
}

void	take_the_next_seat(t_philo *philo)
{
	if (philo->chair_num != philo->philo_num)
		philo->chair_num++; //Eğer filozof son sandalyede otran filozof değilse sandalye no'sunu bir arttır
	else
		philo->chair_num = 1; //Eğer son sandalyede oturuyorsa onu ilk sandalyeye taşı
}

void	print_philo_state(t_philo *philo, char *message, int p_id)
{
	long long	duration;
	
	pthread_mutex_lock(philo->write_lock); //Yazı yazmak üzere
	duration = get_time_ms() - *(philo->start_time);
	pthread_mutex_lock(philo->death_lock); //Ölüm bayrağını kontrol etmek üzere
	if(*(philo->death_flag) == 0) //Eğer filozof ölmemişse
		printf("%lld %d %s\n", duration, p_id, message);
	pthread_mutex_unlock(philo->death_lock);
	pthread_mutex_unlock(philo->write_lock);
}
