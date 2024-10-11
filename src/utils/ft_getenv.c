/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:34:30 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 11:30:22 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *variable)
{
	int		idx;
	int		len;
	char	*value;

	if (ft_strchr(variable, '=') == NULL)
		return (NULL);
	len = 0;
	while (variable[len] != '=')
		len++;
	value = safe_alloc(sizeof(char) * (ft_strlen(&variable[len + 1]) + 1));
	idx = 0;
	len++;
	while (variable[len])
	{
		value[idx] = variable[len];
		len++;
		idx++;
	}
	value[idx] = '\0';
	return (value);
}

char	*ft_getenv(char *variable)
{
	int		idx;
	char	**env;

	env = *get_env();
	idx = 0;
	while (env[idx])
	{
		if (compare_variables(env[idx], variable) == 0)
			return (get_value(env[idx]));
		idx++;
	}
	return (NULL);
}
