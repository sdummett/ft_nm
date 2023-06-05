#include "ft_nm.h"

static int	len_str(unsigned long nb) {
	int	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb) {
		nb = nb / 16;
		len++;
	}
	return (len);
}

char	*utohex(unsigned long nb) {
	char	*str;
	char	*hexbase_low;
	int		len;

	hexbase_low = "0123456789abcdef";
	len = len_str(nb);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	str[len] = 0;
	while (nb) {
		str[len - 1] = *(hexbase_low + nb % 16);
		nb = nb / 16;
		len--;
	}
	return (str);
}