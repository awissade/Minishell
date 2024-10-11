/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_copy_with_malloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:46:58 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/08 01:47:09 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_copy_with_malloc(char **strs)
{
	int		idx;
	char	**new_strs;

	new_strs = malloc(sizeof(char *) * (ft_dblptrlen(strs) + 1));
	if (new_strs == NULL)
		return (NULL);
	idx = 0;
	while (strs[idx])
	{
		new_strs[idx] = ft_strdup(strs[idx]);
		idx++;
	}
	new_strs[idx] = NULL;
	return (new_strs);
}
