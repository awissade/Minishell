/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:56:45 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 20:36:09 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * memcmp - Compare two memory blocks.
 * @s1: A pointer to the first memory block.
 * @s2: A pointer to the second memory block.
 * @n: The number of bytes to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if the first n
 * bytes of s1 are found, respectively, to be less than, equal to, or greater
 * than the first n bytes of s2.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (cs1[i] == cs2[i] && i < (n - 1))
		i++;
	return (((unsigned char *)cs1)[i] - ((unsigned char *)cs2)[i]);
}
