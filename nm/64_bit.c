#include "../includes/nm.h"

void    get_info(struct symtab_command *sym, t_file *file)
{
    uint64_t i;
    struct nlist_64 *array;
    char *strtable;
    t_symbol64  *symbols;
    char *str;

    array = file->ptr + sym->symoff;
    strtable = file->ptr + sym->stroff;
    symbols = (t_symbol64*)malloc(sizeof(t_symbol64));
    file->head = symbols;
    for (i = 0; i < sym->nsyms; i++)
    {
        str = strtable + array[i].n_un.n_strx;
        symbols->type = array[i].n_type & N_TYPE;
        symbols->ext = array[i].n_type & N_EXT;
        symbols->sect = array[i].n_sect;
        symbols->name = ft_strdup(str);
        symbols->value = array[i].n_value;
        if (i + 1 == sym->nsyms)
            symbols->next = NULL;
        symbols->next = (t_symbol64 *)malloc(sizeof(t_symbol64));
        symbols = symbols->next;
    }
}

void    handle_64(t_file *file)
{
    int nmcmds;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;
    int     i;

    header = (struct mach_header_64 *)file->ptr;
    nmcmds = header->ncmds;
    lc = (void*)file->ptr + sizeof(*header);
    for (i = 0; i < nmcmds; i++)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            get_info(sym, file);
            print_symbols(file);
            break;
        }
        lc = (void *)lc + lc->cmdsize;
    }
}