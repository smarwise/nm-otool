/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:40:17 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/21 13:40:21 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/nm.h"

 void    handle_fat64(void *ptr, char *str, int args)
 {
     uint32_t               n;
     uint32_t               i;
     struct fat_header      *header;
     struct fat_arch_64     *arch;

    i = 0;
    header = (struct fat_header *)ptr;
    arch = (struct fat_arch_64 *)(header + 1);
    n = swap(header->nfat_arch);
    while (i < n)
    {
        if ((swap(arch->cputype) == CPU_TYPE_X86_64)\
         || (swap(arch->cputype) == CPU_TYPE_I386 ) )
        {
            nm(ptr + swap(arch->offset), str, args);
            break;
        }
        arch = (struct fat_arch_64*)((void*)arch + sizeof(struct fat_arch_64));
        i++;
    }
 }

 void    handle_fat(void *ptr, char *str, int args)
 {
     uint32_t               n;
     uint32_t               i;
     struct fat_header      *header;
     struct fat_arch        *arch;

    i = 0;
    header = (struct fat_header *)ptr;
    arch = (struct fat_arch *)(header + 1);
    n = swap(header->nfat_arch);
    while (i < n)
    {
        if (swap(arch->cputype) == CPU_TYPE_X86_64) 
        {
            nm(ptr + swap(arch->offset), str, args);
            break;
        }
        arch = (struct fat_arch*)((void*)arch + sizeof(struct fat_arch));
        i++;
    }
 }
