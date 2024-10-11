/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:46:57 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 13:36:26 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * ft_substr - Allocates and returns a substring from the string ’s’
 *	       that begins at index ’start’ and is of maximum size ’len’.
 * @s: The string from which to create the substring.
 * @start: The start index of the substring in the string ’s’.
 * @len: The maximum length of the substring.
 *
 * Return: The substring.
 *	   NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;
	int		tmp;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	tmp = start;
	while (s[start++] && i < len)
		i++;
	start = tmp;
	subs = malloc(sizeof(char) * (i + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	return (subs);
}
