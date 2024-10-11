/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:52:04 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/11 20:15:37 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * memcpy - Copy memory area.
 * @dest: A pointer to the destination memory block.
 * @src: A pointer to the source memory block.
 * @n: The number of bytes to copy.
 *
 * Return: A pointer to the destination memory block (dest).
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == NULL || src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (dst != src)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return ((void *)d);
}
