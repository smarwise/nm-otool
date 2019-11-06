#ifndef OTOOL_H
#define OTOOL_H

#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ar.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <mach-o/fat.h>

typedef struct s_file
{
    void *ptr;
    char *filename;
    int    nb_args;
    int     fd;
}              t_file;

int     print_err(char *str);
void        ft_otool(void *ptr, char *str);
void        handle_64(void *ptr);
void handle_32(void *ptr);
void     printer(int i, uint64_t addr, char *data);
void    handle_arch(void *ptr, char * name);
#endif