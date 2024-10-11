/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:04:47 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 21:45:39 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_variable(char *variable, char **env)
{
	int		idx;
	int		idx1;

	if (compare_variables(variable, "PATH") == 0
		&& get_localvar()->path_unset == 0)
		get_localvar()->path_unset = 1;
	idx = -1;
	while (env[++idx])
		if (!compare_variables(env[idx], variable))
			break ;
	if (env[idx] == NULL)
		return ;
	free(env[idx]);
	idx1 = idx + 1;
	while (env[idx1])
	{
		env[idx] = env[idx1];
		idx++;
		idx1++;
	}
	env[idx] = NULL;
}

int	unset(char **av)
{
	int	idx;

	idx = 1;
	while (av[idx])
	{
		remove_variable(av[idx], *get_env());
		idx++;
	}
	return (0);
}
