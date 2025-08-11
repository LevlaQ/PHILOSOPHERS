/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:28 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/11 19:35:42 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Düşünmenin belirli bir süresi yok. Filozof "düşünüyor" mesajını bastırdık-
	tan hemen sonra sandalye sayısını bir arttırıp bir sonraki rutine girmeliler
	
	Düşünme rutini ayrı
	Yeme-uyuma rutini ayrı

	TODO Sandalye numarasını bir arttıran fonksiyon yaz
*/


/*
	Bir şekilde supervisor'ın kendi rutinin başlangıcı olacak olan gonksiyon olacak
*/
void	*waitress_glaring(void	*philo)
{
	(void)philo;
	printf("Waitress is lusting after blood :D\n");
	return (NULL);
}

int	i_think_therefore_i_am(t_philo *philo)
{
	
}

int	eat_sleep(t_philo *philo)
{
	
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