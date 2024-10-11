/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:44:50 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/11 13:23:19 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	length;

	if (dest == NULL || src == NULL)
		return (0);
	length = 0;
	if (dest_size == 0)
	{
		while (src[length])
			length++;
		return (length);
	}
	while (src[length] != '\0' && dest_size > 1)
	{
		dest[length] = src[length];
		length++;
		dest_size--;
	}
	dest[length] = '\0';
	while (src[length])
		length++;
	return (length);
}
