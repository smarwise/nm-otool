#include "../includes/nm.h"

void    get_info(struct symtab_command *sym, t_file *file)
{
    uint64_t i;
    struct nlist_64 *array;
    char *strtable;

    array = file->ptr + sym->symoff;
    strtable = file->ptr + sym->stroff;
    for (i = 0; i < sym->nsyms; i++)
    {
        printf("%s\n", strtable + array[i].n_un.n_strx);
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
            break;
        }
        lc = (void *)lc + lc->cmdsize;
    }
}