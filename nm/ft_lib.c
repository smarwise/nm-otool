/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:41:04 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:41:08 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

char **sort_output(char **array)
{
    char    *temp;
    int     n;
    int k;

    n = 1;
    while (array[n])
    {
        k = n - 1;
        while (k >= 0)
        {
            if (ft_strcmp(array[k], array[n]) > 0)
            {
                temp = array[n];
                array[n] = array[k];
                array[k] = temp;
            }
            else
                break;
            n--;
            k--;
        }
        n++;
    }
    return (array);
}

int     check_if_exists(char *str, char **array, int i)
{
    int     n;

    n = 0;
    while (n != i)
    {
        if (ft_strcmp(str, array[n]) == 0)
            return (1);
        n++;
    }
    return (0);
}

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
