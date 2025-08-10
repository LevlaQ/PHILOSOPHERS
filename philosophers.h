/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:45:00 by gyildiz           #+#    #+#             */
/*   Updated: 2025/08/10 08:53:21 by gyildiz          ###   ########.fr       */
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

#define MAX 200

typedef pthread_mutex_t mtx;

typedef struct s_philo
{
	int			philo_id;			//Çıktıda filozoflar birbirine karışmasın diye bir değişken
	pthread_t	th_id;			//Oluşturduğum thread'in id'si, fonksiyon thread id'sini buraya yazacak
	int			philo_num;			//Kaç tane filom var
	int			time_die;			//En son yemek yeme başlangıcımdan bu zamana ne zaman açlıktan öleceğim
	int			time_eat;			//Ne kadar sürede yemek yiyorum
	int			time_sleep;			//Ne kadar sürede uyuyorum
	int			num_eat;			//Opsiyonel, bütün filozoflar en az kaç yemek yemeli
	int			meals_eaten;		//Ben kaç defa yemek yedim //LOCK
	long long	last_meal;			//En son yemek yemeye başlamamın üzerinden geçen süre (ya da simülasyon başlama zamanı) //LOCK
	int			chair_num;			//Şu an hangi sandalyede oturuyorum
	int			*death_flag;		//Yaşıyorsam 0, ölüysem 1, Bütün filolar ortak yere bakacak
	mtx			*left_fork;			//Filonun solundaki çatal
	mtx			*right_fork;		//Filonun sağındaki çatal
	mtx			*death_lock;
	mtx			*write_lock;
	mtx			*meals_eaten_lock;
	mtx			*last_meal_lock;
}				t_philo;

/*
	death_flag ylnızca supervisor tarafından erişilebilecek, bu yüzden kilit koymama
	gerek yok gibi
*/
typedef struct s_philo_table
{
	int		death_flag;
	mtx		death_lock;		//Ölüm kilidi ne kadar gerekli, zaten yalnızca gözlemci okuyup yazma yapacak, başka erşien yok
	mtx		write_lock;		//Ekrana aynı anda hepsi yazı yazmaya kalkamasın
	mtx		meals_eaten;	//Filo kaç yemek yediğini yazarken superviser okuma yapmasın
	mtx		last_meal;		//Son yemeğimin zamanını yazarken gözlemci yarım veriyi görüp yazı yazmasın
	t_philo	*philo;
}			t_philo_table;

/* Filozoflar utils */

int		ft_atoi(const char *str);

/* Kullnıcı girdi kontrol fonksiyonları */

int		validate_variables(char **argv);

/* Filozofların masa inşaası fonksiyonları */

void	fill_structs(t_philo *philo, char **argv, mtx *forks, t_philo_table *table);
int		initiliazing_mutexes(t_philo_table *table, mtx *forks);
//void	test_print_philos(t_philo *philos, int count); //TEST

/* Zaman fonksiyonları */

long long	get_time_ms(void);
long long	time_difference(t_philo *philo);

/* Filozof yaşan döngüsü fonksiyonları */

int		simulation_init(t_philo_table *table, mtx *forks, int i);
void	*philo_life_cycle(void *arg);
void	*waitress_glaring(void	*philo);

/* Free fonksiyonları */

void	finish_simulation(t_philo_table *table, mtx *forks);

#endif