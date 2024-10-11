/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:47:45 by ajawad            #+#    #+#             */
/*   Updated: 2024/06/26 09:47:54 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cm_strdup(char *src)
{
	char	*ptr;
	int		length;
	int		i;

	if (src == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(src);
	ptr = safe_alloc(sizeof(char) * (length + 1));
	while (i < length)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
