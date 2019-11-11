 #include "../includes/nm.h"

 void    handle_fat64(void *ptr, char *str, int args)
 {
     uint32_t n;
     uint32_t i;
     struct fat_header *header;
     struct fat_arch_64 *arch;

    i = 0;
    header = (struct fat_header *)ptr;
    arch = (struct fat_arch_64 *)(header + 1);
    n = swap_uint64(header->nfat_arch);
    while (i < n)
    {
        if (i != 0)
            arch = (struct fat_arch_64 *)ptr;
        if ((swap_uint64(arch->cputype) == CPU_TYPE_X86_64)\
         || (swap_uint64(arch->cputype) == CPU_TYPE_I386 ) )
        {
            nm(ptr + swap_uint64(arch->offset), str, args);
            // break;
        }
        ptr = ptr + swap_uint64(arch->size);
        i++;
    }
 }

 void    handle_fat(void *ptr, char *str, int args)
 {
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
        if (i != 0)
            arch = (struct fat_arch *)ptr;
        if ((swap_uint32(arch->cputype) == CPU_TYPE_X86_64)\
         || (swap_uint32(arch->cputype) == CPU_TYPE_I386 ) )
        {
            nm(ptr + swap_uint32(arch->offset), str, args);
            // break;
        }
        ptr = ptr + swap_uint32(arch->size);
        i++;
    }
 }