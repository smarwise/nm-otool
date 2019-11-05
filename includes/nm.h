#include "../libft/libft.h"
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ar.h>
#include <mach-o/fat.h>

typedef struct s_file
{
    void *ptr;
    char *filename;
    int    nb_args;
    int     fd;
}              t_file;

void        ft_nm(t_file *file);
int         print_err(char *str);
void        handle_64(t_file *file);
uint32_t    swap_uint32(uint32_t n);
uint64_t	swap_uint64(uint64_t n);