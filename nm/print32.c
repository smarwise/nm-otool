/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:41:44 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:41:46 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

char        *get_add32(uint32_t add, char c)
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
    char    tag;

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
    char        **array;
    t_symbol32  *sym;
    uint32_t         n;

    n = 0;
    array = (char **)malloc(sizeof(char *) * (file->nbsyms + 1));
    sym = file->head32;
    while (n < file->nbsyms)
    {
        array[n] = ft_strdup(sym->name);
        sym = sym->next;
        n++;
    }
    array[n] = NULL;
    return (sort_output(array));
}

void    print_syms32(char ***prev, t_symbol32 *sym, t_section *sect, char *str)
{
    int b;
    char tag;

    while (sym->next)
    {
        b = 0;
        tag = get_tag32(sym, sect);
        if (ft_strcmp(sym->name, str) == 0)
        {
            if (in_array(*prev, get_add32(sym->value, tag)) == 1)
                b = 1;
            if (b == 0 || (b == 1 && get_tag32(sym, sect) == 'U'))
            {
                ft_putstr(get_add32(sym->value, tag));
                ft_putchar(' ');
                ft_putchar(tag);
                ft_putchar(' ');
                ft_putendl(sym->name);
                break;
            }
        }
        sym = sym->next;
    }
}

void    print_symbols32(t_file *file)
{
    t_symbol32 *sym;
    char        **array;
    char **arr;

    arr = (char**)malloc(sizeof(char *) * (file->nbsyms + 1));
    arr[0] = NULL;
    array = ft_sort32(file);
    print_name(file);
    while (*array)
    {
        sym = file->head32;
        print_syms32(&arr, sym, file->sect, *array);
        array++;
    }
}
