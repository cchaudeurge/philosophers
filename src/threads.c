#include "../include/philo.h"

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
			pthread_mutex_lock(&sim->print_stop_mutex);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->print_stop_mutex);
			pthread_join(sim->monitor, NULL);
			while (--i >= 0)
				pthread_join(sim->philos[i].thread, NULL);
			return (print_error(thread_err));
		}
		i++;
	}
	return (0);
}

void	join_threads(t_sim *sim)
{
	int	i;

	pthread_join(sim->monitor, NULL);
	i = 0;
	while (i < sim->nb_of_philo)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

