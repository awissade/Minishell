/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:30:27 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/25 12:24:14 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str, char sep)
{
	int	idx;
	int	counter;

	idx = 0;
	counter = 0;
	while (str[idx])
	{
		while (str[idx] == sep)
			idx++;
		if (str[idx] != '\0')
			counter++;
		while (str[idx] && (str[idx] != sep))
			idx++;
	}
	return (counter);
}

char	**strsplit(char *str, char sep)
{
	int		idx;
	int		jdx;
	int		kdx;
	char	**strs;

	idx = 0;
	kdx = 0;
	strs = safe_alloc(sizeof(char *) * (count_words(str, sep) + 1));
	while (str[idx])
	{
		while (str[idx] == sep)
			idx++;
		jdx = idx;
		while (str[idx] && str[idx] != sep)
			idx++;
		if (idx > jdx)
		{
			strs[kdx] = ft_strndup(str + jdx, idx - jdx);
			kdx++;
		}
	}
	strs[kdx] = NULL;
	return (strs);
}
