/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:57:03 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/28 11:11:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_locally(t_localvar *localvar)
{
	free(localvar->oldpwd);
	localvar->oldpwd = localvar->pwd;
	localvar->pwd = getcwd(NULL, 0);
}

void	change_oldpwdvar(char **env)
{
	int				idx;
	char			*holder;
	static int		flag;

	idx = -1;
	if (flag == 1)
		get_localvar()->active = 1;
	while (env[++idx])
	{
		if (compare_variables(env[idx], "OLDPWD") == 0)
		{
			holder = ft_getenv("PWD");
			free(env[idx]);
			if (holder == NULL && flag == 0)
			{
				flag = 1;
				env[idx] = ft_strdup("OLDPWD");
			}
			else if (holder != NULL)
				env[idx] = ft_strjoin("OLDPWD=", holder);
			else
				env[idx] = ft_strjoin("OLDPWD=", get_localvar()->oldpwd);
			return ;
		}
	}
}

void	change_pwdvar(char **env)
{
	int		idx;
	char	*holder;

	idx = -1;
	while (env[++idx])
	{
		if (compare_variables(env[idx], "PWD") == 0)
		{
			free(env[idx]);
			holder = getcwd(NULL, 0);
			env[idx] = ft_strjoin("PWD=", cm_strdup(holder));
			free(holder);
			return ;
		}
	}
}

void	change_inenv(char **env)
{
	change_oldpwdvar(env);
	change_pwdvar(env);
}

void	change_pwd(char **env, t_localvar *localvar)
{
	change_locally(localvar);
	change_inenv(env);
}
