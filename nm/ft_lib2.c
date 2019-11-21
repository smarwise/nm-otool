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

int     ft_arraylen(t_symbol64 *sym)
{
    int len;

    len = 0;
    while (sym->next)
    {
        sym = sym->next;
        len++;
    }
    return (len);
}

int     ft_arraylen32(t_symbol32 *sym)
{
    int     len;

    len = 0;
    while (sym->next)
    {
        sym = sym->next;
        len++;
    }
    return (len);
}

char **sort_output(char **array)
{
    char    *temp;
    int     i;
    int     n;

    i = 0;
    n = 0;
    while (array[n])
    {
        if (array[n + 1])
        {
            if (strcmp(array[n], array[n + 1]) > 0)
            {
                temp = array[n];
                array[n] = array[n + 1];
                array[n + 1] = temp;
                sort_output(array);
            }
        }
        else
            return (array);
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
