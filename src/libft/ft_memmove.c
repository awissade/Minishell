/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:53:21 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 13:34:52 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_moving(void *dst, const void *src, size_t len)
{
	size_t	i;
	int		j;

	if (src > dst && src - dst < (int)len)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if (dst > src && dst - src < (int)len)
	{
		j = len - 1;
		while (j >= 0)
		{
			((unsigned char *)dst)[j] = ((unsigned char *)src)[j];
			j--;
		}
	}
	else
		ft_memcpy(dst, src, len);
}

/**
 * memmove - Copy memory area, handling overlapping regions.
 * @dest: A pointer to the destination memory block.
 * @src: A pointer to the source memory block.
 * @n: The number of bytes to copy.
 *
 * Return: A pointer to the destination memory block (dest).
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst || !src)
		return (NULL);
	if (dst == src || len == 0)
		return (dst);
	ft_moving(dst, src, len);
	return (dst);
}
