/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:00:09 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/07 23:11:24 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***get_env(void)
{
	static char	**env;

	return (&env);
}

t_localvar	*get_localvar(void)
{
	static t_localvar	localvar;

	return (&localvar);
}

void	initialize_pwd_oldpwd(void)
{
	char	*holder;

	if (ft_getenv("PWD") == NULL)
	{
		holder = getcwd(NULL, 0);
		add_variable(strjoin("PWD=", holder), *get_env());
		free(holder);
	}
	if (ft_getenv("OLDPWD") == NULL)
		add_variable("OLDPWD", *get_env());
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	*get_env() = get_copy_with_malloc(env);
	initialize_pwd_oldpwd();
	initialize_localvar(get_localvar());
	minishell();
	return (0);
}
