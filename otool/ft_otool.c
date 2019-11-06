#include "../includes/otool.h"

void        ft_print(char *str)
{
    if (ft_strcmp("no", str) != 0)
    {
        ft_putstr(str);
        ft_putendl(":");
    }
}


void        ft_otool(void *ptr, char *str)
{
    unsigned int     magic_nb;

    magic_nb = *(int *)ptr;
    if (magic_nb == MH_MAGIC_64)
    {
        ft_print(str);
        handle_64(ptr);
    }
    else if (magic_nb == MH_MAGIC)
    {
        ft_print(str);
        handle_32(ptr);
    }
    else if (!(ft_strcmp(ft_strsub((char *)ptr, 0, 8), ARMAG)))
        handle_arch(ptr, str);
    else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
    {
        ft_print(str);
        handle_fat(ptr, str);
    }
    else
    {
        if (ft_strcmp(str, "no") != 0)
            ft_putendl("Error: Not a valid binary file");
        return;
    }
}