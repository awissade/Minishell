/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:44:28 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/25 12:24:27 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;
	int		tmp;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (cm_strdup(""));
	tmp = start;
	while (s[start++] && i < len)
		i++;
	start = tmp;
	subs = safe_alloc(sizeof(char) * (i + 1));
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
