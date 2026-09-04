#include "../include/philo.h"

//Should S_T be at the beginning?
static int	init_sim(t_sim *sim, char **argv)
{
	sim->nb_of_philo = ft_atoll(argv[1]);
	sim->time_to_die = ft_atoll(argv[2]);
	sim->time_to_eat = ft_atoll(argv[3]);
	sim->time_to_sleep = ft_atoll(argv[4]);
	if (argv[5])
		sim->min_nb_meals = (int)ft_atoll(argv[5]);
	else
		sim->min_nb_meals = -1;
	sim->start_time = get_time_ms();
	sim->philos = malloc(sim->nb_of_philo * sizeof(*sim->philos));
	if (!sim->philos)
		return (print_error(malloc_err));
	sim->forks  = malloc(sim->nb_of_philo * sizeof(sim->forks));
	if (!sim->forks)
		return (free(sim->philos), print_error(malloc_err));
	sim->stop = 0;
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (free(sim->philos), free(sim->forks), print_error(mutex_err));
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		return (free(sim->philos), free(sim->forks), print_error(mutex_err));
	}
	return (0);
}

static void	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_of_philo)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->nb_of_philo];
		sim->philos[i].sim = sim;
		i++;
	}
}

static int	init_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_of_philo)
	{
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i].mutex);
			return (print_error(mutex_error));
		}
		i++;
	}
	return (0);
}

int	initiate_simulation(t_sim *sim, char **argv)
{
	if (init_sim(sim, argv) != 0)
		return (1);
	init_philos(sim);
	if (init_forks(sim) != 0)
	{
		cleanup_sim(sim);
		return (1);
	}
	return (0);
}

int	init_threads(t_sim *sim)
{
	int	i;

	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim) != 0)
		return (print_error(thread_err));
	i = 0;
	while (i < sim-> nb_of_philo)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
			&sim->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(&sim->forks[i].mutex);
			return (print_error(mutex_error));
		}
		i++;
	}
	return (0);
