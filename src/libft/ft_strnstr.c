/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:57:14 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 21:21:50 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (str == NULL || to_find == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (str == to_find || to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (str[i + j] == to_find[j] && (i + j) < len)
		{
			if (!str[i + j] && !to_find[j])
				return ((char *)(str + i));
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
		j = 0;
	}
	return (NULL);
}
