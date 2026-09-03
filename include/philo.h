#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*For printf*/
# include <stdio.h>
/*For threads*/
# include <pthread.h>

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_sim	t_sim;

typedef struct	s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal;
	int			meals_eaten;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_sim		*sim;
}	t_philo;

typedef struct	s_sim
{
	int				nb_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int				min_nb_meals;
	long				start_time;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	t_fork			*forks;
}	t_sim;

#endif
