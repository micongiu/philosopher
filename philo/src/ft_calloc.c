#include "../philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n)
	{
		*p++ = 0;
		--n;
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	char	*p;

	if (!n && !size)
		return (NULL);
	p = malloc(size * n);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, size * n);
	return (p);
}
