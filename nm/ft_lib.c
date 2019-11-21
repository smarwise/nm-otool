/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:40:41 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:40:44 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

uint32_t	swap(uint32_t n)
{
	return ((n >> 24) & 0xff) |\
	((n << 8) & 0xff0000) |\
	((n >> 8) & 0xff00) |\
	((n << 24) & 0xff000000);
}
