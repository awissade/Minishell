/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:55:05 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 21:05:39 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	rev;

	if (s == NULL)
		return (NULL);
	rev = ft_strlen(s);
	if (c == '\0')
		return (&((char *)s)[rev]);
	while (rev >= 0)
	{
		if (s[rev] == (char)c)
			return (&((char *)s)[rev]);
		rev--;
	}
	return (NULL);
}
