#include "../philo.h"

int	ft_check_arguments(char **argu)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while(argu[i])
	{
		k = 0;
		if (!argu[i] || !argu[i][k])
			return (0);
		while (argu[i][k])
		{
			if (argu[i][k] <= '0' || argu[i][k] >= '9')
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return(printf("Too many or too few arguments\n"), 0);
	if (!ft_check_arguments(argv))
		return(printf("Wrong inpunt\n"), 0);
	printf("ok\n");
	return (1);
}