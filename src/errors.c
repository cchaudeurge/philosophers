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
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	free(sim->philos);
	free(sim->forks);
}
