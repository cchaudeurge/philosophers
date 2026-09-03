#include "../include/philo.h"

static int	usage_error(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	printf("Arguments:\n");
	printf(" number_of_philosophers Number of philosophers and forks.\n");
	printf(" time_to_die Time in ms before a philosopher "
		"dies without eating.\n");
	printf(" time_to_eat Time in ms a philosopher spends eating.\n");
	printf(" time_to_sleep Time in ms a philosopher spends sleeping.\n");
	printf(" number_of_times_each_philosopher_must_eat Optional. Simulation "
		"stops when all philosophers have eaten this many times.\n");
	return (1);
}

int	main(int argc, char **argv)
{
	//t_sim	sim;

	if (argc != 5 && argc != 6)
		return (usage_error());
	init_sim(&sim, argv);
	return (0);
}
