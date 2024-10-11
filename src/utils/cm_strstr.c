/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:12:47 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/29 13:18:54 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cm_strstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	if (str == NULL || to_find == NULL)
		return (-2);
	i = 0;
	j = 0;
	if (str == to_find)
		return (0);
	while (str[i])
	{
		while (str[i + j] == to_find[j])
		{
			if (!str[i + j] && !to_find[j])
				return (i);
			j++;
		}
		if (to_find[j] == '\0')
			return (i);
		i++;
		j = 0;
	}
	return (-1);
}
