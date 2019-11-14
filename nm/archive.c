/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise </var/mail/root>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 06:56:18 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/11 06:56:21 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void    print_filename(char *lib_name, char *file_name)
{
    ft_putstr("\n");
    ft_putstr(lib_name);
    ft_putstr("(");
    ft_putstr(file_name);
    ft_putendl("):");
}

 void       nm(void *ptr, char *name, int args)
 {
    uint32_t     magic_nb;
    t_file *file;
 
    file = (t_file*)malloc(sizeof(t_file));
    file->filename = ft_strdup(name);
    file->ptr = ptr;
    file->nb_args = args;
    magic_nb = *(uint32_t *)ptr;
    if (magic_nb == MH_MAGIC_64)
        handle_64(file);
    else if (magic_nb == MH_MAGIC)
        handle_32(file);
    else if (magic_nb == FAT_MAGIC_64 || magic_nb == FAT_CIGAM_64)
        handle_fat64(ptr, file->filename, args);
    else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
        handle_fat(ptr, file->filename, args);
    else if (!(ft_strcmp(ft_strsub((char *)ptr, 0, 8), ARMAG)))
       handle_arch(file->ptr, file->filename, args);
    else
        return;
 }

void    handle_arch(void *ptr, char * name, int args)
{
  struct ar_hdr *file;
  char *file_member;
  int size;
  void *tmp;
  int diff;
  int temp;

  file = (struct ar_hdr*)(ptr + SARMAG);
  while (ft_strlen(file->ar_size) > 0)
  {
    size = ft_atoi(file->ar_size);
    file_member = (void *)file + sizeof(struct ar_hdr);
    temp = ft_atoi(ft_strstr(file_member - sizeof(struct ar_hdr), AR_EFMT1) + ft_strlen(AR_EFMT1));
    diff = temp - ft_strlen(file_member);
    if (ft_strstr(file_member, "SYMDEF") == NULL)
    {
        print_filename(name, file_member);
        tmp = ((void *)file_member) + ft_strlen(file_member) + diff;
        nm(tmp, file_member, args);
    }
    file = (struct ar_hdr*)((void *)file_member + size);
  }
}
