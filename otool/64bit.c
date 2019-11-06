#include "../includes/otool.h"

char	*itoa_base(uint64_t value, int base)
{
	long	nb;
	char	*str;
	int		len;

    len = 9;
	nb = (long)value;
    if (nb < 0)
		nb = nb * -1;
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (nb == 0)
		return ("0");
	str[len] = '\0';
	len--;
	while (nb)
	{
		str[len] = (nb % base < 10) ? nb % base + '0' : nb % base - 10 + 65;
		nb = nb / base;
		len--;
	}
    return (ft_strcmp(str, "") == 0 ? ft_itoa_base(value, base) : str);
}

void        print_add(uint64_t add)
{
    char    *str;
    int     diff;
    int     len;
    char    *padding;

    padding = "000000000";
    ft_putstr("0000000");
    str = ft_tolower(itoa_base(add, 16));
    if (ft_strlen(str) < 9)
    {
        len = ft_strlen(str);
        diff = 9 - len;
        ft_putstr(ft_strsub(padding, 0, diff));
    }
    ft_putstr(str);
}

char     *to_hex(unsigned char c)
{
    int num;

    num = c;
    return (ft_itoa_base(num, 16));
}

void     printer(int i, uint64_t addr, char *data)
{
    
    if (i % 16 == 0)
    {
        if (i != 0)
            ft_putchar('\n');
        print_add(addr + i);
        ft_putstr("\t");
    }
    if (ft_strlen(to_hex(data[i])) == 1)
        ft_putstr("0");
    ft_putstr(ft_tolower(to_hex(data[i])));
    ft_putchar(' ');
}



void    print_sect(struct section_64 *section, void *ptr)
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

void    handle_sects(struct load_command *lc, void *ptr)
{
    
    struct segment_command_64 *seg;
    struct section_64 *section;
    int nb_sect;
    int i;
    void *section_addr;

    i = 0;
    seg = (struct segment_command_64 *)((void *)lc);
    nb_sect = seg->nsects;
    section = (void *)seg + sizeof(*seg);
     while (i < nb_sect)
    {
        if (ft_strcmp(section->sectname, "__text") == 0 && ft_strcmp(section->segname, "__TEXT") == 0)
        {
            section_addr = (void *)ft_itoa(section->addr);
            print_sect(section, ptr);
        }
        i++;
        section = (void *)section + sizeof(*section);
    }
}

void handle_64(void *ptr)
{
    int nmcmds;
    struct mach_header_64 *header;
    struct load_command *lc;
    int     i;

    header = (struct mach_header_64 *)ptr;
    nmcmds = header->ncmds;
    lc = (void*)ptr + sizeof(*header);
    for (i = 0; i < nmcmds; i++)
    {
        if (lc->cmd == LC_SEGMENT_64)
        {
            handle_sects(lc, ptr);
            // break;
        }
        lc = (void *)lc + lc->cmdsize;
    }
}