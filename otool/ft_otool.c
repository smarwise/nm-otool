#include "../includes/otool.h"

void        ft_otool(void *ptr, char *str)
{
    unsigned int     magic_nb;

    magic_nb = *(int *)ptr;
    if (magic_nb == MH_MAGIC_64)
    {
        ft_putstr(str);
        ft_putendl(":");
        handle_64(ptr);
    }
    else if (magic_nb == MH_MAGIC)
    {
        ft_putstr(str);
        ft_putendl(":");
        handle_32(ptr);
    }
    else if (!(ft_strcmp(ft_strsub((char *)ptr, 0, 8), ARMAG)))
    {
        handle_arch(ptr, str);
    }
    else
    {
        ft_putendl("Error: Not a valid binary file");
        return;
    }
}