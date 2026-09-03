#include "../include/philo.c"

static long long	ft_atoll(const char *str)
{
	long long	nbr;
	long long	sign;

	nbr = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

//Should S_T be at the beginning?
int	init_sim(t_sim *sim, char **argv)
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
	sim->philos = (t_philo *)malloc(sim->nb_of_philo * sizeof(t_philo));
	if (!sim->philos)
		return (1);
	sim->forks  = (t_fork *)malloc(sim->nb_of_philo * sizeof(t_fork));
	if (!sim->forks)
		return (free(sim->philos), 1);
	sim->stop = 0;
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (free(sim->philos), free(sim->forks), 1);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		return (free(sim->philos), free(sim->forks), 1);
	}
	return (0);
}
