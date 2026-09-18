#include "../include/philo.h"

static int	check_enough_meals(t_sim *sim)
{
	int	enough_meals;

	pthread_mutex_lock(&sim->meal_nb_mutex);
	if (sim->enough_meals == sim->nb_of_philo)
		enough_meals = 1;
	else
		enough_meals = 0;
	pthread_mutex_unlock(&sim->meal_nb_mutex);
	return (enough_meals);
}

int	check_state(t_philo philo)
{
	t_sim	*sim;

	sim = philo.sim;
	pthread_mutex_lock(&philo.meal_mutex);
	if (check_enough_meals(sim) == 1)
	{
		pthread_mutex_lock(&sim->print_stop_mutex);
		sim->stop = 1;
		pthread_mutex_unlock(&sim->print_stop_mutex);
		pthread_mutex_unlock(&philo.meal_mutex);
		return (1);
	}
	if (get_time_ms() - philo.last_meal >= sim->time_to_die)
	{
		pthread_mutex_lock(&sim->print_stop_mutex);
		sim->stop = 1;
		printf("%lld %d died\n", get_time_ms() - sim->start_time, philo.id);
		pthread_mutex_unlock(&sim->print_stop_mutex);
		pthread_mutex_unlock(&philo.meal_mutex);
		return (1);
	}
	return (0);
}

/*void	set_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
}*/
