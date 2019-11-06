#include "../includes/otool.h"

void    print_sect32(struct section *section, void *ptr)
{
    char *data;
    
    uint64_t i = 0;
    ft_putendl("Contents of (__TEXT,__text) section");
    data = ptr+section->offset;
    while (i < section->size)
    {
        printer(i, section->addr, data);
        if (i + 1 == section->size)
            ft_putchar('\n');
        i++;
    }
}

void    handle_sects32(struct load_command *lc, void *ptr)
{
    
    struct segment_command *seg;
    struct section *section;
    int nb_sect;
    int i;
    void *section_addr;
    (void)ptr;

    i = 0;
    seg = (struct segment_command *)((void *)lc);
    nb_sect = seg->nsects;
    section = (void *)seg + sizeof(*seg);
    while (i < nb_sect)
    {
        if (ft_strcmp(section->sectname, "__text") == 0 && ft_strcmp(section->segname, "__TEXT") == 0)
        {
            section_addr = (void *)ft_itoa(section->addr);
            print_sect32(section, ptr);
        }
        i++;
        section = (void *)section + sizeof(*section);
    }
}

void handle_32(void *ptr)
{
    int nmcmds;
    struct mach_header *header;
    struct load_command *lc;
    int     i;

    header = (struct mach_header *)ptr;
    nmcmds = header->ncmds;
    lc = ptr + sizeof(*header);
    for (i = 0; i < nmcmds; i++)
    {
        if (lc->cmd == LC_SEGMENT)
        {
            handle_sects32(lc, ptr);
            // break;
        }
        lc = (void *)lc + lc->cmdsize;
    }
}