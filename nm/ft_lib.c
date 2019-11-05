#include "../includes/nm.h"

int     print_err(char *str)
{
    ft_putendl(str);
    return (0);
}

char	*itoa_base(uint64_t value, int base)
{
	long	nb;
	char	*str;
	int		len;

    len = 9;
	nb = (long)value;
    if (nb < 0)
		nb = nb * -1;
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (nb == 0)
		return ("0");
	str[len] = '\0';
	len--;
	while (nb)
	{
		str[len] = (nb % base < 10) ? nb % base + '0' : nb % base - 10 + 65;
		nb = nb / base;
		len--;
	}
    return (ft_strcmp(str, "") == 0 ? ft_itoa_base(value, base) : str);
}

uint32_t	swap_uint32(uint32_t n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0xFF00FF);
	return ((n << 16) | (n >> 16));
}

uint64_t	swap_uint64(uint64_t n)
{
	n = ((n << 8) & 0xFF00FF00FF00FF00ULL) \
		| ((n >> 8) & 0x00FF00FF00FF00FFULL);
	n = ((n << 16) & 0xFFFF0000FFFF0000ULL) \
		| ((n >> 16) & 0x0000FFFF0000FFFFULL);
	return ((n << 32) | (n >> 32));
}