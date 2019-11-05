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

char    get_tag(t_symbol64 *sym, t_section *section)
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
        printf("................ %s ", itoa_base(sym->sect, 16));
        printf("%s ", itoa_base(section->bss, 16));
        printf("%s ", itoa_base(section->data, 16));
        printf("%s \n", itoa_base(section->text, 16));
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

void    print_symbols(t_file *file)
{
    t_symbol64 *sym;

    sym = file->head;
    while (sym->next)
    {
        // printf("%s ", get_add(sym->value));
        printf("%c ", get_tag(sym, file->sect));
        printf("%s %llu %llu %llu\n", sym->name, sym->ext, sym->sect, sym->type);
        sym = sym->next;
    }
}