/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:51:07 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/15 15:46:36 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_full(t_philo *philo, int *counter)
{
	int	num_e;
	int	n;

	num_e = philo->num_eat;
	n = philo->philo_num;
	pthread_mutex_lock(philo->meals_eaten_lock);
	if (philo->meals_eaten >= num_e)
	{
		pthread_mutex_unlock(philo->meals_eaten_lock);
		(*counter)++;
	}
	else
		pthread_mutex_unlock(philo->meals_eaten_lock);
	if (*(counter) >= n)
	{
		pthread_mutex_lock(philo->write_lock);
		pthread_mutex_lock(philo->death_lock);
		*(philo->death_flag) = 1;
		pthread_mutex_unlock(philo->death_lock);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	return (0);
}

/*
	print_philo_state() fonksiyonumda kilit sırası write_lock->death_lock->death_unlock->write_lock
	şeklinde bu yüzden burada da aynı sıraya uymaya çalışıyorum
*/
static int	check_philo_death(t_philo *philo)
{
	long long	duration;

	if (time_difference(philo) > philo->time_die)
	{
		//pthread_mutex_unlock(philo->last_meal_lock); //Karşılaştırmayı yaptım, şimdi serbest bırak
		pthread_mutex_lock(philo->write_lock);
		pthread_mutex_lock(philo->death_lock);
		*(philo->death_flag) = 1;
		duration = get_time_ms() - *(philo->start_time);
		printf("%lld %d died\n", duration, philo->philo_id);
		pthread_mutex_unlock(philo->death_lock);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	return (0);
}

/*
	Bir şekilde supervisor'ın kendi rutinin başlangıcı olacak olan fonksiyon olacak

	Bütün filozofları sonsuz döngüde dolanarak ölüm durumu var mı veya bütün
	filolarım gerçekten doymuş mu diye bir gözlem yapmaya çalışıyorum

	Filozoflarımı i'den i-N ye kadar sürekli döndürmem lazım, bütün filoları tek 
	tek gezip datalarını kontrol edebilmeli
*/
void	*waitress_glaring(void *philo)
{
	t_philo		*philos;
	int			counter;
	int			i;
	int			n;

	philos = (t_philo *)philo;
	i = 0;
	n = philos[0].philo_num;
	while(42)
	{
		if (i == 0)
			counter = 0; //Her tur için sayım yapıyor!!! (Bu turda hepsi tok mu)
		if (check_philo_death((philos + i)))
			break ;
		if (philos[0].num_eat > 0) //Eğer ilgili opsiyon girilmişse
		{
			if (check_full(philos + i, &counter))
				break ;
		}
		i = (i + 1) % n;
		usleep(100);
	}
	return (NULL);
}