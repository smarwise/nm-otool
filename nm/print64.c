#include "../includes/nm.h"

char        *get_add(uint64_t add)
{
    char    *str;
    int     diff;
    int     len;
    char    *padding;
    char    *zeros;

    padding = ft_strdup("00000000");
    zeros = ft_strdup("0000000");
    str = ft_tolower(itoa_base(add, 16));
    len = ft_strlen(str);
    diff = 9 - len;
    str = ft_strjoin(ft_strsub(padding, 0, diff), str);
    str = ft_strjoin(zeros, str);
    return (str);
}

void    print_symbols(t_file *file)
{
    t_symbol64 *sym;

    sym = file->head;
    while (sym->next)
    {
        printf("%s ", get_add(sym->value));
        printf("%s %llu %llu %llu %llu\n", sym->name, sym->ext, sym->sect, sym->type, sym->value);
        sym = sym->next;
    }
}