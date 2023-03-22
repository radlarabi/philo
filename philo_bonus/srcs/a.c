/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:12:01 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/21 14:07:48 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#define MAX_MEALS 10

int num_philosophers;
pthread_mutex_t chopsticks[5];
sem_t *sem;
int meals_eaten[5];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    struct timeval tv;

    for (int i = 0; i < MAX_MEALS; i++) {
        printf("Philosopher %d is thinking...\n", id);
        usleep(rand() % 1000 + 1000);

        sem_wait(sem);
        pthread_mutex_lock(&chopsticks[id]);
        printf("fork %d\n", id);
        pthread_mutex_lock(&chopsticks[(id + 1) % num_philosophers]);
        printf("fork %d\n", id);
        sem_post(sem);

        printf("Philosopher %d is eating...\n", id);
        gettimeofday(&tv, NULL);
        printf("Philosopher %d started eating at %ld.%06ld\n", id, tv.tv_sec, tv.tv_usec);
        meals_eaten[id] = meals_eaten[id] + 1;
        usleep(rand() % 1000 + 1000);
        gettimeofday(&tv, NULL);
        printf("Philosopher %d finished eating at %ld.%06ld\n", id, tv.tv_sec, tv.tv_usec);

        pthread_mutex_unlock(&chopsticks[id]);
        pthread_mutex_unlock(&chopsticks[(id + 1) % num_philosophers]);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [number of philosophers]\n", argv[0]);
        exit(1);
    }

    num_philosophers = atoi(argv[1]);

    // Initialize chopsticks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Initialize sem
    sem = sem_open("semaphore", O_CREAT, 0644, num_philosophers - 1);

    // Create philosopher processes
    pid_t philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i] = fork();
        if (philosophers[i] == 0) {
            int id = i;
            philosopher(&id);
            exit(0);
        }
    }

    // Wait for all philosopher processes to finish
    for (int i = 0; i < num_philosophers; i++) {
        waitpid(philosophers[i], NULL, 0);
    }

    // Print out meals eaten
    printf("\nMeals eaten:\n");
    for (int i = 0; i < num_philosophers; i++) {
        printf("Philosopher %d ate %d meals\n", i, meals_eaten[i]);
    }

    // Destroy chopsticks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    // Close sem
    sem_close(sem);
    sem_unlink("semaphore");

    return 0;
}
