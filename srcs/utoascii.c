#include "ft_nm.h"

static int	sizeof_n(unsigned int n) {
	int				size;
	unsigned int	tmp;

	if (n) {
		size = 0;
		tmp = n;
		while (tmp) {
			tmp = tmp / 10;
			size++;
		}
	}
	else
		size = 1;
	return (size);
}

static char	*protected_malloc(char *str, int size_n) {
	str = malloc(sizeof(char) * size_n + 1);
	if (!str)
		return (0);
	str[size_n] = 0;
	return (str);
}

static void	inttoascii(char *str, unsigned long int tmp, int size_n) {
	while (tmp) {
		str[size_n--] = tmp % 10 + 48;
		tmp = tmp / 10;
	}
}

char	*utoascii(unsigned int n) {
	int					size_n;
	unsigned long int	tmp;
	char				*str;

	str = NULL;
	tmp = n;
	size_n = sizeof_n(n) - 1;
	str = protected_malloc(str, sizeof_n(n));
	if (n && str)
		inttoascii(str, tmp, size_n);
	else if (!n && str)
		str[size_n] = '0';
	else
		return (0);
	return (str);
}