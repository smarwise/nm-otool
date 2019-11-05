#include "../libft/libft.h"
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ar.h>
#include <mach-o/fat.h>

typedef struct	s_section
{
	uint32_t	index;
	uint32_t	text;
	uint32_t	data;
	uint32_t	bss;
}				t_section;

typedef struct  s_symbol64
{
    char    *name;
    uint64_t    value;
    uint64_t    type;
    uint64_t    sect;
    uint64_t    ext;
    struct  s_symbol64 *next;
}               t_symbol64;


typedef struct s_file
{
    void *ptr;
    char *filename;
    int    nb_args;
    int     fd;
    t_symbol64 *head;
    t_section *sect;
}              t_file;

typedef struct  s_symbol_32
{
    char    *name;
    uint32_t    value;
    uint32_t    type;
    uint32_t    sect;
    struct  s_symbol32 *next;
}               t_symbol32;

void        ft_nm(t_file *file);
int         print_err(char *str);
void        handle_64(t_file *file);
uint32_t    swap_uint32(uint32_t n);
uint64_t	swap_uint64(uint64_t n);
void    print_symbols(t_file *file);
char	*itoa_base(uint64_t value, int base);
uint64_t		ppc_64(uint64_t n);