#include "../include/philo.h"

void	release_forks(t_fork *first_fork, t_fork *second_fork)
{
	if (first_fork)
		pthread_mutex_unlock(&first_fork->mutex);
	if (second_fork)
		pthread_mutex_unlock(&second_fork->mutex);
}

void	*one_philo_rout(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (NULL);
}

void	*mult_philo_rout(t_philo *philo, t_fork *first_fork, t_fork *second_fork)
{
	while (1)
	{
		pthread_mutex_lock(&first_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&second_fork->mutex);
		if (print_status(philo, "has taken a fork") != 0)
		{
			release_forks(first_fork, second_fork);
			break ;
		}
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time_ms();
		print_status(philo, "is eating");
		pthread_mutex_unlock(&philo->meal_mutex);
		ft_wait(philo->sim->time_to_eat);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->sim->min_nb_meals)
		{
			pthread_mutex_lock(&philo->sim->meal_nb_mutex);
			philo->sim->enough_meals++;
			pthread_mutex_unlock(&philo->sim->meal_nb_mutex);
		}
		release_forks(first_fork, second_fork);
		if (print_status(philo, "is sleeping") != 0)
			break ;
		ft_wait(philo->sim->time_to_sleep);
		if (print_status(philo, "is thinking") != 0)
			break ;
	}
	return (NULL);
}
	
void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_fork	*first_fork;
	t_fork	*second_fork;

	philo = (t_philo *)arg;
	if (philo->sim->nb_of_philo == 1)
		return (one_philo_rout(philo));
//	if (philo->id % 2 == 0)
//	{
//		first_fork = philo->left_fork;
//		second_fork = philo->right_fork;
//	}
//	else
//	{
//		ft_wait(1);
//		first_fork = philo->right_fork;
//		second_fork = philo->left_fork;
//	}
//	if (philo->id < philo->sim->nb_of_philo)
//	{
	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
//	}
//	else
//	{
//		first_fork = philo->right_fork;
//		second_fork = philo->left_fork;
//	}
	if (philo->id % 2 == 0)
		ft_wait(1);
	return (mult_philo_rout(philo, first_fork, second_fork));
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		i;
	long long	check_start;
	long long	elapsed;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		check_start = get_time_ms();
		while (i < sim->nb_of_philo)
		{
			if (check_state(sim->philos[i]) == 1)
				return (NULL);
			i++;
		}
		elapsed = get_time_ms() - check_start;
		if (elapsed <= 9)
			ft_wait((10 - elapsed) / 2);
	}
	return (NULL);
}
