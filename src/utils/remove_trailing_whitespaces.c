/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_trailing_whitespaces.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:11:39 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/31 20:04:21 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str)
{
	int	idx;
	int	len;

	idx = 0;
	while (ft_isspace(str[idx]))
		idx++;
	len = 0;
	while (str[idx])
	{
		if (!ft_isspace(str[idx]))
			len++;
		else if (ft_isspace(str[idx]) \
				&& !ft_isspace(str[idx + 1]) && str[idx + 1])
			len++;
		idx++;
	}
	return (len);
}

char	*remove_trailing_whitspaces(char *str)
{
	char	*newstr;
	int		idx1;
	int		idx2;

	if (str == NULL)
		return (NULL);
	newstr = safe_alloc(sizeof(char) * (count_len(str) + 1));
	idx1 = 0;
	idx2 = 0;
	while (ft_isspace(str[idx1]))
		idx1++;
	while (str[idx1])
	{
		if (!ft_isspace(str[idx1]))
			newstr[idx2++] = str[idx1];
		else if (ft_isspace(str[idx1]) \
				&& !ft_isspace(str[idx1 + 1]) && str[idx1 + 1])
			newstr[idx2++] = ' ';
		idx1++;
	}
	return (newstr[idx2] = '\0', newstr);
}
