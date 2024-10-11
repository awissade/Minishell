/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:11:02 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/12 13:57:39 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		length;
	int		i;

	if (src == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(src);
	ptr = malloc(sizeof(char) * (length + 1));
	if (ptr == NULL)
	{
		return (0);
	}
	while (i < length)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
