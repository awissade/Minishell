/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:49:51 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/12 13:58:18 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	inset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*cm_strdup(const char *src, int start, int end)
{
	char	*dest;
	int		s_idx;
	int		d_idx;
	int		len;

	len = end - start + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	s_idx = start;
	d_idx = 0;
	while (s_idx <= end && src[s_idx])
	{
		dest[d_idx] = src[s_idx];
		s_idx++;
		d_idx++;
	}
	dest[d_idx] = '\0';
	return (dest);
}

/**
 * ft_strtrim - make a copy of ’s1’ with the characters specified in
 *		'set' removed from the beginning and the end of the string.
 * @s1: The string to be trimmed.
 * @set: The reference set of characters to trim.
 *
 * Return: The trimmed string.
 *	   NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (inset(s1[i], set) == 1)
		i++;
	start = i;
	if (s1[start] == '\0')
	{
		str = ft_strdup("");
		return (str);
	}
	while (s1[i])
		i++;
	i--;
	while (inset(s1[i], set) == 1)
		i--;
	end = i;
	str = cm_strdup(s1, start, end);
	return (str);
}
