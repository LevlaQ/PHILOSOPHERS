/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:28 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/13 19:24:32 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
	Düşünmenin belirli bir süresi yok. Filozof "düşünüyor" mesajını bastırdık-
	tan hemen sonra sandalye sayısını bir arttırıp bir sonraki rutine girmeliler
	
	Düşünme rutini ayrı
	Yeme-uyuma rutini ayrı
*/

/*
	50 ms'lik döngüler ile döndürsün
	usleep(1000) => 1 ms
	I need a conventer!

	Uzun sleep sürelerini 50'şer millisaniye bölmek istiyorum.
	Dilimleme sebebim uzun uyku sürelerinde bile superviser gözlem
	yapabilsin ve 10 ms kuralına yaklaşalım
*/
void	activity_duration(long long ms)
{
	long long	us;
	long long	deadline;

	us = 1000 * ms; //FIXME 1000LL yazılabilir
	deadline = get_time_ms() + ms;
	while (us > 0 && get_time_ms() <= deadline)
	{
		if (us > 50000)
		{
			usleep(50000); //50 ms usleep yapsın
			us = (deadline - get_time_ms()) * 1000;
		}
		else
		{
			usleep(us);
			us = (deadline - get_time_ms()) * 1000;
		}
	}
}

void	i_think_therefore_i_am(t_philo *philo)
{
	print_philo_state(philo, "is thinking", philo->philo_id); //Mesajını ekrana bastırdı
	take_the_next_seat(philo); //Sandalye numarasını bir arttırdı
}

void	eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork); //Önce çatallarını aldırıyorum
	print_philo_state(philo, "has taken a fork", philo->philo_id);
	pthread_mutex_lock(philo->left_fork);
	print_philo_state(philo, "has taken a fork", philo->philo_id);
	pthread_mutex_lock(philo->last_meal_lock); //Son yemek yediği zaman yazacak, o yüzden lockuyorum
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(philo->last_meal_lock);//Son yemek zamanı yazıldı, lock'u açıyorum
	print_philo_state(philo, "is eating", philo->philo_id); //Yemek yiyor yazısı
	activity_duration((long long)philo->time_eat); //O kadar süre kadar bekliyor
	pthread_mutex_lock(philo->meals_eaten_lock); //meals_eaten değişkeninde artış yapılması lazım, bu yüzden kilitliyorum
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meals_eaten_lock); //meals_eaten değişkeni arttırıldı, bu yüzden unlock ediyorum
	pthread_mutex_unlock(philo->left_fork); 
	pthread_mutex_unlock(philo->right_fork);
	print_philo_state(philo, "is sleeping", philo->philo_id);
	activity_duration((long long)philo->time_sleep);
	take_the_next_seat(philo);
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