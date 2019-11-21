/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:43:18 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:43:19 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

int     map_file_to_memory(char *str, struct  stat *buf, int *fd, char **ptr)
{
    if ((*fd = open(str, O_RDONLY)) < 0)
    {
        ft_putstr("Error: Open fail\n");
        return (0);
    }
    if (fstat(*fd, buf) < 0)
    {
        ft_putstr("Error: Fstat fail\n");
        return (0);
    }
    if ((*ptr = mmap(0, buf->st_size, PROT_READ,
    MAP_PRIVATE, *fd, 0)) == MAP_FAILED)
    {
        ft_putstr("Error: Mmap fail\n");
        return (0);
    }
    return(1);
}

int          print_error(char *str)
{
    ft_putendl(str);
    return (EXIT_FAILURE);
}

int          main(int argc, char **argv)
{
    int     fd;
    char    *ptr;
    struct  stat buf;
    int n;

    n = 1;
    if (argc < 2)
        return print_error("Error: Missing args\n");
    else
    {
        while (n < argc)
        {
            if (!map_file_to_memory(argv[n], &buf, &fd, &ptr))
                return (EXIT_FAILURE);
            ft_otool(ptr, argv[n]);
            if ((munmap(ptr, buf.st_size)) < 0)
                return print_error("Error: Munmap fail\n");
            close(fd);
            n++;
        }
    }
    return (EXIT_SUCCESS);
}
