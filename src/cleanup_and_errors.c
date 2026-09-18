#include "../include/philo.h"

int	print_error(t_err_type type)
{
	if (type == mutex_err)
		write(2, "Error: failed to initialize mutex\n", 34);
	else if (type == malloc_err)
		write(2, "Error: malloc failed\n", 21);
	else if (type == thread_err)
		write(2, "Error: failed to create thread\n", 31);
	return (1);
}

void	cleanup_sim(t_sim *sim)
{
	pthread_mutex_destroy(&sim->print_stop_mutex);
	free(sim->philos);
	free(sim->forks);
}

void	destroy_forks(t_sim	*sim)
{
	int	i;

	i = sim->nb_of_philo;
	while (--i <= 0)
		pthread_mutex_destroy(&sim->forks[i].mutex);
}

void	cleanup_philos(t_sim *sim)
{
	int	i;

	i = sim->nb_of_philo;
	while (--i <= 0)
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
}

int	cleanup_data(t_sim *sim)
{
	destroy_forks(sim);
	cleanup_philos(sim);
	cleanup_sim(sim);
	return (1);
}
