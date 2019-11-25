/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_bit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:38:03 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:38:06 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void    get_info(struct symtab_command *sym, t_file *file)
{
    struct nlist_64             *array;
    char                        *strtable;
    t_symbol64                  *symbols;

    array = file->ptr + sym->symoff;
    strtable = file->ptr + sym->stroff;
    symbols = (t_symbol64*)malloc(sizeof(t_symbol64));
    file->head = symbols;
    file->nbsyms = sym->nsyms;
    while (file->i < sym->nsyms)
    {
        file->str = strtable + array[file->i].n_un.n_strx;
        if (ft_strlen(file->str) > 0)
        {
            symbols->type = array[file->i].n_type & N_TYPE;
            symbols->ext = array[file->i].n_type & N_EXT;
            symbols->sect = array[file->i].n_sect;
            symbols->name = ft_strdup(file->str);
            symbols->value = array[file->i].n_value;
            if (file->i + 1 == sym->nsyms)
                symbols->next = NULL;
            symbols->next = (t_symbol64 *)malloc(sizeof(t_symbol64));
            symbols = symbols->next;
        }
        file->i++;
    }
}

void        get_sect_info(struct load_command *lc, t_file *file)
{
    struct segment_command_64       *seg;
	struct section_64               *sect;
	uint32_t                        i;

	seg = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < (seg->nsects))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT) \
			&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
			file->sect->text = file->sect->index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_DATA) \
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			file->sect->data = file->sect->index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_BSS) \
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			file->sect->bss = file->sect->index + 1;
		++(file->sect->index);
	}
}

void    handle_64(t_file *file)
{
    int                             nmcmds;
    struct mach_header_64           *header;
    struct load_command             *lc;
    struct symtab_command           *sym;
    int                             i;

    header = (struct mach_header_64 *)file->ptr;
    nmcmds = header->ncmds;
    lc = (void*)file->ptr + sizeof(*header);
    file->sect = (t_section *)malloc(sizeof(t_section));
    file->sect->index = 0;
    file->i = 0;
    for (i = 0; i < nmcmds; i++)
    {
        if (lc->cmd == LC_SEGMENT_64)
            get_sect_info(lc, file);
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            get_info(sym, file);
            print_symbols(file);
        }
        lc = (void *)lc + lc->cmdsize;
    }
}
