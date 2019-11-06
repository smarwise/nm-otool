#include "../includes/otool.h"

int     print_err(char *str)
{
    ft_putendl(str);
    return (0);
}

uint32_t	swap_uint32(uint32_t n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0xFF00FF);
	return ((n << 16) | (n >> 16));
}