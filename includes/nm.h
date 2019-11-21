#ifndef NM_H
#define NM_H

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
    int     n;
    t_symbol64 *head;
    t_symbol32 *head32;
    t_section *sect;
}              t_file;

 void    handle_fat64(void *ptr, char *str, int args);
void        ft_nm(t_file *file);
int         print_err(char *str);
void        handle_64(t_file *file);
uint32_t    swap(uint32_t n);
void    print_symbols(t_file *file);
char	*itoa_base(uint64_t value, int base);
int     ft_arraylen(t_symbol64 *sym);
char **sort_output(char **array);
char **remove_dupes(char **array);
void        handle_32(t_file *file);
void    print_symbols32(t_file *file);
char        *get_add(uint64_t add, char c);
int     ft_arraylen32(t_symbol32 *sym);
int         init(char *name, int argc);
void       nm(void *ptr, char *name, int args);
void    handle_fat(void *ptr, char *str, int args);
 void    handle_arch(void *ptr, char * name, int args);

 #endif