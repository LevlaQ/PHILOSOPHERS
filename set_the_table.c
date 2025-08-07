/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:22:19 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/07 18:49:11 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


static void fill_the_struct(t_philo *philo, char **argv, int philo_id)
{
	int	i;
	
	i = 0;
	while(argv[i])
	{
		if (i == 0)
			philo->philo_num = ft_atoi(argv[i]);
		else if (i == 1)
			philo->time_die = ft_atoi(argv[i]);
		else if (i == 2)
			philo->time_eat = ft_atoi(argv[i]);
		else if (i == 3)
			philo->time_sleep = ft_atoi(argv[i]);
		else if (i == 4)
			philo->num_eat = ft_atoi(argv[i]);
		i++;
	}
	philo->philo_id = philo_id; //Filonun kim olduğunu etiketi
}

/*
	Bu fonksiyon sadece kullanıcıdan gelen veriler
	için yerleştirme işlemi yapıyor.
*/
void	fill_structs(t_philo *philo, char **argv)
{
	int	i; //Argüman sayacı
	
	i = 0;
	while (i < ft_atoi(argv[0]))
	{
		fill_the_struct(philo + i, argv, i + 1);
		i++;
	}
}

void	fill_structs_main(t_philo *philo, char **argv)
{
	fill_structs(philo, argv);
}

/* TEST */
// void test_print_philos(t_philo *philos, int count)
// {
//     for (int i = 0; i < count; ++i)
//     {
//         printf("Filozof %d (philo_id):\n", philos[i].philo_id);  
//         printf("  philo_num   (number_of_philosophers): %d\n", philos[i].philo_num);
//         printf("  time_die    (time_to_die, ms): %d\n",       philos[i].time_die);
//         printf("  time_eat    (time_to_eat, ms): %d\n",       philos[i].time_eat);
//         printf("  time_sleep  (time_to_sleep, ms): %d\n",     philos[i].time_sleep);
//         printf("  num_eat     (number_of_times_each_philosopher_must_eat): %d\n\n",
//                philos[i].num_eat);
//     }
// }