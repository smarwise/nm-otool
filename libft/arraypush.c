/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraypush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 11:04:21 by smarwise          #+#    #+#             */
/*   Updated: 2018/07/30 18:53:00 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**arraypush(char **array, char *str)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	array[i] = ft_strdup(str);
	array[i + 1] = NULL;
	return (array);
}
