/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:42:37 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:42:38 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

char      *get_filename(char *lib_name, char *file_name)
{
  char        *str;
  char        *str1;
  char        *str2;

  str = ft_strjoin(lib_name, "(");
  str1 = ft_strjoin(str, file_name);
  str2 = ft_strjoin(str1, ")");
  return (str2);
}

void    handle_arch(void *ptr, char *name)
{
  struct ar_hdr *file;
  char          *file_member;
  t_ints        *ints;
  void          *tmp;
  char          *rname;

  file = (struct ar_hdr*)(ptr + SARMAG);
  ints = (t_ints*)malloc(sizeof(ints));
  while (ft_strlen(file->ar_size) > 0)
  {
    ints->size = ft_atoi(file->ar_size);
    file_member = (void *)file + sizeof(struct ar_hdr);
    ints->temp = ft_atoi(ft_strstr(file_member - sizeof(struct ar_hdr),
    AR_EFMT1) + ft_strlen(AR_EFMT1));
    ints->diff = ints->temp - ft_strlen(file_member);
    if (ft_strstr(file_member, "SYMDEF") == NULL)
    {
        rname = get_filename(name, file_member);
        tmp = ((void *)file_member) + ft_strlen(file_member) + ints->diff;
        ft_otool((void*)tmp, rname);
    }
    file = (struct ar_hdr*)((void *)file_member + ints->size);
  }
}
