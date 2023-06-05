#include "ft_nm.h"

int sstrlen(char *str) {
	int i = 0;

	while (str && str[i])
		i++;
	return i;
}
