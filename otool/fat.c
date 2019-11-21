/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:42:45 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:42:47 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/otool.h"

 void    handle_fat(void *ptr)
 {
     uint32_t           n;
     uint32_t           i;
     struct fat_header  *header;
     struct fat_arch    *arch;

    i = 0;
    header = (struct fat_header *)ptr;
    arch = (struct fat_arch *)(header + 1);
    n = swap(header->nfat_arch);
    while (i < n)
    {
        if (swap(arch->cputype) == CPU_TYPE_X86_64) 
        {
            ft_otool(ptr + swap(arch->offset), "no");
            break;
        }
        arch = (struct fat_arch*)((void*)arch + sizeof(struct fat_arch));
        i++;
    }
 }
