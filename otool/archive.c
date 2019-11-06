#include "../includes/otool.h"

char    *get_filename(char *lib_name, char *file_name)
{
  char *str;
  char *str1;
  char *str2;

  str = ft_strjoin(lib_name, "(");
  str1 = ft_strjoin(str, file_name);
  str2 = ft_strjoin(str1, ")");
  return (str2);

}

void    handle_arch(void *ptr, char * name)
{
  struct ar_hdr *file;
  char *file_member;
  int size;
  void *tmp;
  int diff;
  int temp;
  char *rname;

  file = (struct ar_hdr*)(ptr + SARMAG);
  while (ft_strlen(file->ar_size) > 0)
  {
    size = ft_atoi(file->ar_size);
    file_member = (void *)file + sizeof(struct ar_hdr);
    temp = ft_atoi(ft_strstr(file_member - sizeof(struct ar_hdr),
    AR_EFMT1) + ft_strlen(AR_EFMT1));
    diff = temp - ft_strlen(file_member);
    if (ft_strstr(file_member, "SYMDEF") == NULL)
    {
        rname = get_filename(name, file_member);
        tmp = ((void *)file_member) + ft_strlen(file_member) + diff;
        ft_otool((void*)tmp, rname);
    }
    file = (struct ar_hdr*)((void *)file_member + size);
  }
}