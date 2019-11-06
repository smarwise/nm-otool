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
    int         m;
}				t_section;

typedef struct  s_symbol64
{
    char    *name;
    uint64_t    value;
    uint64_t    type;
    uint64_t    sect;
    uint64_t    ext;
    char        tag;
    struct  s_symbol64 *next;
}               t_symbol64;


typedef struct  s_symbol_32
{
    char    *name;
    uint32_t    value;
    uint32_t    type;
    uint32_t    sect;
    uint64_t    ext;
    struct  s_symbol_32 *next;
}               t_symbol32;

typedef struct s_file
{
    void *ptr;
    char *filename;
    int    nb_args;
    int     fd;
    t_symbol64 *head;
    t_symbol32 *head32;
    t_section *sect;
}              t_file;


void        ft_nm(t_file *file);
int         print_err(char *str);
void        handle_64(t_file *file);
uint32_t    swap_uint32(uint32_t n);
uint64_t	swap_uint64(uint64_t n);
void    print_symbols(t_file *file);
char	*itoa_base(uint64_t value, int base);
uint64_t		ppc_64(uint64_t n);
int     ft_arraylen(t_symbol64 *sym);
char **sort_output(char **array);
char **remove_dupes(char **array);
void        handle_32(t_file *file);
void    print_symbols32(t_file *file);
char        *get_add(uint64_t add, char c);
int     ft_arraylen32(t_symbol32 *sym);
int         init(char *name, int argc);
void    handle_arch(void *ptr, char * name);
 void       nm(void *ptr, char *name);
 void    handle_fat(void *ptr, char *str);