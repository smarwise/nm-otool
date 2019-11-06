#include "../includes/nm.h"

char        *get_add32(uint64_t add, char c)
{
    char    *str;
    int     diff;
    int     len;
    char    *padding;

    padding = ft_strdup("00000000");
    str = ft_tolower(itoa_base(add, 16));
    len = ft_strlen(str);
    diff = 8 - len;
    str = ft_strjoin(ft_strsub(padding, 0, diff), str);
    return (c == 'U' ? "        " : str);
}

char    get_tag32(t_symbol32 *sym, t_section *section)
{
    char tag;

    if (sym->type == N_ABS)
		tag = sym->ext ? 'A' : 'a';
    else if (sym->type == N_UNDF)
        tag = 'U';
    else if (sym->type == N_INDR)
		tag = sym->ext ? 'I' : 'i';
    else if (sym->type == N_SECT)
	{
		if (sym->sect == section->bss)
			tag =  sym->ext ? 'B' : 'b';
		else if (sym->sect == section->data)
			tag = sym->ext ? 'D' : 'd';
		else if (sym->sect == section->text)
			tag = sym->ext ? 'T' : 't';
		else
			tag = sym->ext ? 'S' : 's';
	}
    else
        tag = '0';
    return (tag);
}

char    **ft_sort32(t_file *file)
{
    char **array;
    t_symbol32 *sym;
    int n;

    n = 0;
    array = (char **)malloc(sizeof(char *) * (ft_arraylen32(file->head32) + 1));
    sym = file->head32;
    while (sym->next)
    {
        array[n] = ft_strdup(sym->name);
        sym = sym->next;
        n++;
    }
    array[n] = NULL;
    return (sort_output(array));
}

void    print_symbols32(t_file *file)
{
    t_symbol32 *sym;
    char    **array;
    char    **arr;
 
    arr = ft_sort32(file);
    array = remove_dupes(arr);
    file->nb_args > 2 ? ft_putstr(file->filename) : ft_putstr("");
    file->nb_args > 2 ? ft_putendl(":") : ft_putstr("");
    while (*array)
    {
        sym = file->head32;
        while (sym->next)
        {
            if (ft_strcmp(sym->name, *array) == 0 && ((get_tag32(sym, file->sect)) != '0'))
            {
                ft_putstr(get_add32(sym->value, get_tag32(sym, file->sect)));
                ft_putchar(' ');
                ft_putchar(get_tag32(sym, file->sect));
                ft_putchar(' ');
                ft_putendl(sym->name);
                break;
            }
            sym = sym->next;
        }
        array++;
    }
}