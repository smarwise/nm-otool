/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:12:08 by smarwise          #+#    #+#             */
/*   Updated: 2018/06/09 08:45:45 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_tolower(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (c[i] >= 'A' && c[i] <= 'Z')
			c[i] = c[i] + 32;
		i++;
	}
	return (c);
}