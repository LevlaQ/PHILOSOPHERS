/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:22:19 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 09:24:41 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	NOTE Bütün filozofları aynı anda başlatmak gibi bir senkronizasyon
	yapmaktan vazgeçtim, çünkü bunsuz çalışan kodlar da var
*/

static void	fill_the_struct_per_philo(t_philo *philo, char **argv, int philo_id)
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
	printf("Philo ID: %d\n", philo->philo_id); //TEST
}

static void	reach_the_forks_per_philo(t_philo *philo, mtx *forks, t_philo_table *table)
{
	int	id;
	int	p_num;
	
	id = philo->philo_id;
	printf("Philo id in forks func: %d\n", id); //TEST
	p_num = philo->philo_num;
	philo->meals_eaten = 0;
	philo->chair_num = id; //Başta filo idleri ile SANDALYE NO birbirine eşit
	printf("Philo chair num: %d\n", philo->chair_num); //TEST
	philo->right_fork = &(forks[id - 1]);
	printf("Right fork philo 1: %d\n", id - 1); //TEST
	philo->left_fork = &(forks[(id % p_num)]);
	printf("Left fork philo 1: %d\n",(id % p_num)); //TEST
	philo->write_lock = &(table->write_lock);
	philo->meals_eaten_lock = &(table->meals_eaten);
	philo->last_meal_lock = &(table->last_meal);
	philo->death_flag = &(table->death_flag);
	philo->death_lock = &(table->death_lock);
}


/*
Bu fonksiyon sadece kullanıcıdan gelen veriler
için yerleştirme işlemi yapıyor.
*/
void	fill_structs(t_philo *philo, char **argv, mtx *forks, t_philo_table *table)
{
	int	i;
	
	i = 0;
	while (i < ft_atoi(argv[0]))
	{
		fill_the_struct_per_philo(philo + i, argv, i + 1);
		reach_the_forks_per_philo(philo + i, forks, table);
		i++;
	}
	table->philo = philo; //t_philo_table içinde bulunan philo pointerın altına filozoflarımın arrayini yerleştirmeye çalışıyorum
}

/*
	Manueldeki şu cümleden ötürü her bir thread_mutex_t
	tipi yapının bir defa başlatılması gerektiğini anlıyorum
	ve bu fonksiyonu yazıyorum
	Bütün threadlerde bu kilitlerin initialized edilmesi için
	threadler oluşturulmadan kilitleri başlatıyorum
	Yanlış isem beni düzelt
*/
int	initiliazing_mutexes(t_philo_table *table, mtx *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(table->death_lock), NULL) != 0)
		return (finish_simulation(table, forks), 0);
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
		return (finish_simulation(table, forks), 0);
	if (pthread_mutex_init(&(table->meals_eaten), NULL) != 0)
		return (finish_simulation(table, forks), 0);
	if (pthread_mutex_init(&(table->last_meal), NULL) != 0)
		return (finish_simulation(table, forks), 0);
	while (i < table->philo[0].philo_num)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (finish_simulation(table, forks), 0);
		i++;
	}
	return (1);
}

/*
	Mutex + condition variable kullanarak threadleri bekletip, sonra
	hepsini aynı anda simülasyona sokmaya çalışıyorum. İlgili çatal
	atamalarının da yapılması lazım. Ve aynı zamanda ortak struct'taki
	diğer elemanlara
*/
int	simulation_init(t_philo_table *table, mtx *forks, int i)
{
	pthread_t	waitress;
	int			philo_num;

	philo_num = table->philo[0].philo_num;
	if (pthread_create(&waitress, NULL, &waitress_glaring, table->philo) != 0) //HACK
		return (finish_simulation(table, forks), 0);
	while(i < philo_num)
	{
		if (pthread_create(&(table->philo[i].th_id), NULL, &philo_life_cycle,\
		 table->philo) != 0)
			return (finish_simulation(table, forks), 0); //HACK
		table->philo[i].last_meal = get_time_ms(); //Thread başladığı anda start time'ı almak istiyorum
		i++;
	}
	i = 0;
	while(i < philo_num)
	{
		if (pthread_join(table->philo[i].th_id, NULL) != 0)
			return (finish_simulation(table, forks), 0);
		i++;
	}
	if (pthread_join(waitress, NULL) != 0)
		return (finish_simulation(table, forks), 0);
	return (1);
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