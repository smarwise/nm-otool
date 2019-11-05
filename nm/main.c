#include "../includes/nm.h"

int     map_file(t_file *file, struct stat *buf)
{
    if ((file->fd = open(file->filename, O_RDONLY)) < 0)
        return (print_err("Error: Open fail\n"));
    if (fstat(file->fd, buf) < 0)
        return (print_err("Error: Fstat fail\n"));
    if (S_ISDIR(buf->st_mode))
        return (print_err("Error: Arg is a dir"));
    if ((file->ptr = mmap(0, buf->st_size, PROT_READ, MAP_PRIVATE,\
    file->fd, 0)) == MAP_FAILED)
        return (print_err("Error: Mmap fail\n"));
    return(1);
}

int          main(int argc, char **argv)
{
    int     n;
    struct  stat buf;
    t_file  *file;

    n = 1;
    file = (t_file *)malloc(sizeof(t_file));
    if (argc < 2)
        ft_putendl("Error: Put binary to process");
    else
    {
        while (n < argc)
        {
            file->filename = ft_strdup(argv[n]);
            file->nb_args = argc;
            if (!map_file(file, &buf))
                return (EXIT_FAILURE);
            ft_nm(file);
            if ((munmap(file->ptr, buf.st_size)) < 0)
                return print_err("Error: Munmap fail\n");
            close(file->fd);
            n++;
        }
    }
    return (EXIT_SUCCESS);
}