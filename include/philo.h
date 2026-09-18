#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*For printf*/
# include <stdio.h>
/*For threads*/
# include <pthread.h>
/*For write*/
# include <unistd.h>
/*For gettimeofday*/
# include <sys/time.h>
/*For malloc, free*/
# include <stdlib.h>

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_sim	t_sim;

typedef struct	s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_sim			*sim;
}	t_philo;

typedef struct	s_sim
{
	int				nb_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_nb_meals;
	int				enough_meals;
	pthread_mutex_t	meal_nb_mutex;
	long long		start_time;
	int				stop;
	pthread_mutex_t	print_stop_mutex;
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		monitor;
}	t_sim;

typedef enum	s_err_type
{
	mutex_err,
	malloc_err,
	thread_err
}	t_err_type;

/*init_data.c*/
int			initiate_simulation(t_sim *sim, char **argv);
/*threads.c*/
int			init_threads(t_sim *sim);
void		join_threads(t_sim *sim);
/*utils.c*/
long long	get_time_ms(void);
long long	ft_atoll(const char *str);
int			print_status(t_philo *philo, char *msg);
void		ft_wait(long long time_to_wait);
/*cleanup_and_errors.c*/
int			print_error(t_err_type type);
void		cleanup_sim(t_sim *sim);
void		destroy_forks(t_sim	*sim);
int			cleanup_data(t_sim *sim);
void		cleanup_philos(t_sim *sim);
/*routines.c*/
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
/*monitor.c*/
int			check_state(t_philo philo);

#endif
