/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:45:00 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/07 20:18:47 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <string.h> //memset()
# include <stdlib.h> //malloc(), free()
# include <unistd.h> //write(), usleep()
# include <sys/time.h> //gettimeofday()
# include <pthread.h> //pthread functions
# include <stdio.h> //printf()

/*
	DÜŞÜNMEK ÇATAL BEKLEMEK
*/

typedef struct s_fork
{
	pthread_mutex_t	fork; //Bunun adresi mutex fonksiyonlarına verilecek
	int				fork_id; //Hangi çatalı aldığını bileyim diye
}					t_fork;

typedef struct s_philo
{
	int			philo_num; //Kaç tane filom var
	int			time_die; //En son yemek yeme başlangıcımdan bu zamana ne zaman açlıktan öleceğim
	int			time_eat; //Ne kadar sürede yemek yiyorum
	int			time_sleep; //Ne kadar sürede uyuyorum
	int			num_eat; //Opsiyonel, bütün filozoflar en az kaç yemek yemeli
	int			philo_id; //Çıktıda filozoflar birbirine karışmasın diye bir değişken
	pthread_t	thread_id; //Oluşturduğum thread'in id'si, fonksiyon thread id'sini buraya yazacak
	int			num_eaten; //Ben kaç defa yemek yedim
	long long	eat_start; //En son yemek yemeye başlamamın üzerinden geçen süre (ya da simülasyon başlama zamanı)
	int			chair_num; //Şu an hangi sandalyede oturuyorum
	int			*death_flag; //Yaşıyorsam 0, ölüysem 1, Bütün filolar ortak yere bakacak
	t_fork		*left; //Filonun solundaki çatal
	t_fork		*right; //Filonun sağındaki çatal
}				t_philo;

void	*ft_calloc(size_t count, size_t size);
int		error_main(int argc, char **argv);
int		validate_variables(char **argv);
int		check_chars(char **el);
int		modified_atoi_limits(char *str);
int		ft_atoi(const char *str);

/* Filozofların masa inşaası fonksiyonları */

void	fill_structs_main(t_philo *philo, char **argv);
void	test_print_philos(t_philo *philos, int count); //TEST

#endif