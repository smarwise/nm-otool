 #include "../includes/nm.h"
 
 void       ft_nm(t_file *file)
 {
    uint32_t     magic_nb;
    void         *ptr;

    ptr = file->ptr;
    magic_nb = *(uint32_t *)ptr;
    if (magic_nb == MH_MAGIC_64)
        handle_64(file);
    else if (magic_nb == MH_MAGIC)
        handle_32(file);
    // else if (magic_nb == FAT_MAGIC_64 || magic_nb == FAT_CIGAM_64)
        // handle_fat64(ptr, file->filename, file->nb_args);
    else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
        handle_fat(ptr, file->filename, file->nb_args);
    else if (!(ft_strcmp(ft_strsub((char *)ptr, 0, 8), ARMAG)))
        handle_arch(file->ptr, file->filename, file->nb_args);
    else
    {
        ft_putendl("Error: Not a valid binary file");
        return;
    }
 }