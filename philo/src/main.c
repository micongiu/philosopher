#include "../philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		err_exit("Too many or too few arguments\n");
	if (!ft_check_arguments(argv))
		err_exit("Wrong inpunt\n");
	ft_init_info(argv, &info);
	ft_init_philo_mutex(&info);
	return (1);
}
