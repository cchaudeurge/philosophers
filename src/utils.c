#include "../include/philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	ft_atoll(const char *str)
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
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}

int	print_status(t_philo *philo, char *msg)
{
	t_sim	*sim;
	int		stop;

	sim = philo->sim;
	pthread_mutex_lock(&sim->print_stop_mutex);
	stop = sim->stop;
	if (!stop)
		printf("%lld %d %s\n", get_time_ms() - sim->start_time, philo->id, msg);
	pthread_mutex_unlock(&sim->print_stop_mutex);
	return (stop);
}

void	ft_wait(long long time_to_wait)
{
	long long	time_start;
	long long	time_current;

	time_start = get_time_ms();
	time_current = time_start;
	while (time_current - time_start < time_to_wait)
	{
		usleep(20);
		time_current = get_time_ms();
	}
}
