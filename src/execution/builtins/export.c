/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:33:38 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 13:23:01 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *var)
{
	int		len;
	int		idx;
	char	*varname;

	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	varname = safe_alloc(sizeof(char) * (len + 1));
	idx = 0;
	while (var[idx] != '=' && var[idx])
	{
		varname[idx] = var[idx];
		idx++;
	}
	varname[idx] = '\0';
	return (varname);
}

int	swap_vars(char *var1, char *var2)
{
	int	idx;

	idx = 0;
	while (var1[idx] == var2[idx] && var1[idx] && var2[idx])
		idx++;
	if (var1[idx] > var2[idx])
		return (1);
	return (0);
}

char	**get_env_copy_sorted(char **env_copy)
{
	int		idx;
	int		jdx;
	char	*temp;

	idx = -1;
	while (env_copy[++idx])
	{
		jdx = idx + 1;
		while (env_copy[jdx])
		{
			if (swap_vars(get_varname(env_copy[idx])
					, get_varname(env_copy[jdx])))
			{
				temp = env_copy[idx];
				env_copy[idx] = env_copy[jdx];
				env_copy[jdx] = temp;
			}
			jdx++;
		}
	}
	return (env_copy);
}

int	builtin_export(char **av)
{
	int	idx;
	int	status;

	if (av[1] == NULL)
	{
		print_env(get_env_copy_sorted(get_copy_with_malloc(*get_env())));
		return (0);
	}
	idx = 1;
	status = 0;
	while (av[idx])
	{
		if (export_variable(av[idx]) == 1)
			status = 1;
		idx++;
	}
	return (status);
}
