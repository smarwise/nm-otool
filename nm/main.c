/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:41:31 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:41:33 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int     map_file(t_file *file, struct stat *buf)
{
    if ((file->fd = open(file->filename, O_RDONLY)) < 0)
        return (print_err("Error: Open fail\n"));
    if (fstat(file->fd, buf) < 0)
        return (print_err("Error: Fstat fail\n"));
    if (S_ISDIR(buf->st_mode))
        return (print_err("Error: Arg is a dir"));
    if ((file->ptr = mmap(0, buf->st_size, PROT_READ, MAP_PRIVATE,\
    file->fd, 0)) == MAP_FAILED)
        return (print_err("Error: Mmap fail\n"));
    return(1);
}


int         init(char *name, int argc)
{
    struct  stat buf;
    t_file  *file;

    if (ft_strcmp("->", name) != 0)
    {
        file = (t_file *)malloc(sizeof(t_file));
        file->filename = ft_strdup(name);
        file->nb_args = argc;
        file->n = 0;
        file->part_of_lib = 0;
        if (!map_file(file, &buf))
            return (-1);
        ft_nm(file);
        if ((munmap(file->ptr, buf.st_size)) < 0)
            return print_err("Error: Munmap fail\n");
        close(file->fd);
    }
    else
        return (2);
    return (0);
}

int          main(int argc, char **argv)
{
    int     n;

    n = 1;
    if (argc < 2)
        ft_putendl("Error: Put binary to process");
    else
    {
        while (n < argc)
        {
            if (init(argv[n], argc) == 2)
                n++;
            n++;
        }
    }
    return (EXIT_SUCCESS);
}
