/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:55:49 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 20:31:56 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * memchr - Search for a character in a memory block.
 * @s: A pointer to the memory block to be searched.
 * @c: The character to be located.
 * @n: The maximum number of bytes to search.
 *
 * Return: A pointer to the first occurrence of the character c within the
 * first n bytes of the memory area, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
