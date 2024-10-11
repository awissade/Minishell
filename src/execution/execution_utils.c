/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:33:58 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/04 17:19:37 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*path_variable;
	char	*cmd_path;
	int		idx;

	path_variable = ft_getenv("PATH");
	if (path_variable == NULL && get_localvar()->path_unset == 0)
		path_variable = cm_strdup(get_localvar()->default_path);
	else if (path_variable == NULL && get_localvar()->path_unset == -1)
		return (cmd);
	else if (path_variable == NULL && get_localvar()->path_unset == 1)
		return (cmd);
	cmd = strjoin("/", cmd);
	paths = strsplit(path_variable, ':');
	idx = 0;
	while (paths[idx] != NULL)
	{
		cmd_path = strjoin(paths[idx], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		idx++;
	}
	return (NULL);
}

char	*get_command(char *command)
{
	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			else
			{
				ft_putstr_fd(command, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				panic(PERMISSION_DENIED);
			}
		}
		else
			return (NULL);
	}
	return (get_cmd_path(command));
}

int	isbuiltin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	else
		return (0);
}
