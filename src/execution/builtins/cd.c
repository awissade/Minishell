/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:54 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/28 16:49:50 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **av)
{
	char	*path;

	if (ft_dblptrlen(av) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (av[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: home directory not found\n", 2);
			return (1);
		}
	}
	else
		path = av[1];
	if (-1 == chdir(path))
	{
		perror(path);
		return (1);
	}
	change_pwd(*get_env(), get_localvar());
	return (0);
}
