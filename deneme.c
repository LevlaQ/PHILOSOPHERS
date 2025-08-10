#include <pthread.h>
#include <stdio.h>
#include "philosophers.h"  // t_philo, t_philo_table deklarasyonları

// philosophers.h içinde örnek güncellenmiş t_philo_table:
// typedef struct s_table {
//     int             death_flag;
//     pthread_mutex_t death_lock;          // ölüm kilidi (death lock)
//     pthread_mutex_t write_lock;          // yazma kilidi (write lock)
//     pthread_mutex_t meals_eaten_mutex;   // yemek sayısı kilidi (meals eaten lock)
//     pthread_mutex_t last_meal_mutex;     // son yemek kilidi (last meal lock)
//     // Başlangıç senkronizasyonu için eklenenler:
//     pthread_mutex_t start_mutex;         // başlangıç mutex (start mutex)
//     pthread_cond_t  start_cond;          // başlangıç koşul değişkeni (start condition variable)
//     int             ready;               // hazır bayrağı (ready flag)
//     long long       start_time;          // simülasyon başlangıç zamanı (simulation start time)
// } t_philo_table;

// t_philo yapısına eklenecek alanlar:
//     pthread_mutex_t *start_mutex;   // başlangıç mutex pointer (start mutex pointer)
//     pthread_cond_t  *start_cond;    // başlangıç koşul değişkeni pointer (start condition variable pointer)
//     int             *ready_flag;    // hazır bayrağı pointer (ready flag pointer)
//     long long       *start_time;    // başlangıç zamanı pointer (start time pointer)

extern long long get_time_ms(void);                // Zaman ölçüm fonksiyonu
extern void *philosopher_routine(void *arg);       // Filozof döngü fonksiyonu (thread routine)

void simulation_init(t_philo *philo, pthread_mutex_t *forks, t_philo_table *table)
{
    int i;
    int N = philo->philo_num;  // Filozof sayısı
    long long t0;

    // 1) Senkronizasyon primitiflerini başlat
    pthread_mutex_init(&table->start_mutex, NULL);   // start_mutex init
    pthread_cond_init(&table->start_cond, NULL);     // start_cond init
    table->ready = 0;                                // ready bayrağı sıfırla

    // 2) Ortak başlangıç zamanını al
    t0 = get_time_ms();
    table->start_time = t0;

    // 3) Her filozof struct'ını doldur
    for (i = 0; i < N; i++) {
        philo[i].last_meal       = t0;              // son yemeği başlangıç olarak ata
        philo[i].meals_eaten     = 0;               // yenen yemek sayısını sıfırla
        philo[i].left_fork        = &forks[i];       // sol çatal pointer
        philo[i].right_fork       = &forks[(i + 1) % N]; // sağ çatal pointer
        // Ortak bayrak ve mutex pointer'ları
        philo[i].death_flag       = &table->death_flag;
        philo[i].write_lock       = &table->write_lock;
        philo[i].meals_eaten_lock = &table->meals_eaten_mutex;
        philo[i].last_meal_lock   = &table->last_meal_mutex;
        // Başlangıç senkronizasyonu için
        philo[i].start_mutex      = &table->start_mutex;
        philo[i].start_cond       = &table->start_cond;
        philo[i].ready_flag       = &table->ready;
        philo[i].start_time       = &table->start_time;
    }

    // 4) Filozof thread'lerini oluştur
    for (i = 0; i < N; i++) {
        if (pthread_create(&philo[i].th_id, NULL,
                           philosopher_routine, &philo[i]) != 0) {
            perror("pthread_create");
            return;
        }
    }

    // 5) "Başlat" sinyalini ver
    pthread_mutex_lock(&table->start_mutex);
    table->ready = 1;
    pthread_cond_broadcast(&table->start_cond);      // Tüm thread'leri uyandır
    pthread_mutex_unlock(&table->start_mutex);

    // 6) Thread'lerin bitişini bekle (join)
    for (i = 0; i < N; i++) {
        pthread_join(philo[i].th_id, NULL);
    }
}
