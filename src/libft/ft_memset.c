/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:09:39 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/04 20:35:04 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * memset - Fill a block of memory with a specified byte value.
 * @b: A pointer to the memory block to be filled.
 * @c: The byte value to be set in each byte of the block.
 * @len: The number of bytes to be filled with the specified value.
 *
 * Return: A pointer to the original memory area (b).
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	if (b == NULL)
		return (NULL);
	if (len == 0)
		return (b);
	a = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		a[i++] = c;
	}
	return (b);
}
