/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:43:09 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:43:11 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void        ft_print(char *str, char *ptr, int n)
{
    if (ft_strcmp("no", str) != 0)
    {
        ft_putstr(str);
        ft_putendl(":");
    }
    if (n == 1)
        handle_64(ptr);
}


void        ft_otool(void *ptr, char *str)
{
    unsigned int     magic_nb;

    magic_nb = *(int *)ptr;
    if (magic_nb == MH_MAGIC_64)
        ft_print(str, ptr, 1);
    else if (magic_nb == MH_MAGIC)
    {
        ft_print(str, ptr, 0);
        handle_32(ptr);
    }
    else if (!(ft_strcmp(ft_strsub((char *)ptr, 0, 8), ARMAG)))
        handle_arch(ptr, str);
    else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
    {
        ft_print(str, ptr, 0);
        handle_fat(ptr);
    }
    else
    {
        if (ft_strcmp(str, "no") != 0)
            ft_putendl("Error: Not a valid binary file");
        return;
    }
}
