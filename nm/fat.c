 #include "../includes/nm.h"

 void    handle_fat(void *ptr, char *str)
 {
     (void)str;
     uint32_t n;
     uint32_t i;
     struct fat_header *header;
     struct fat_arch *arch;

    i = 0;
    header = (struct fat_header *)ptr;
    arch = (struct fat_arch *)(header + 1);
    n = swap_uint32(header->nfat_arch);
    while (i < n)
    {
        if (i == 0)
        {
            nm(ptr + swap_uint32(arch->offset), "no");
            ptr = ptr + swap_uint32(arch->size);
        }
        else
        {
            arch = (struct fat_arch *)ptr;
            nm(ptr + swap_uint32(arch->offset), "no");
            ptr = ptr + swap_uint32(arch->size);
        }
        i++;
    }
 }