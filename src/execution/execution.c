/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:56:31 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 18:22:18 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	panic(NO_SUCH_FILE_OR_DIR);
}

int	execute(t_execcmd *exec)
{
	char		*holder;
	char		**av;
	struct stat	path_stat;

	holder = exec->av[0];
	exec->av[0] = get_command(exec->av[0]);
	if (exec->av[0] == NULL)
		error(holder);
	stat(exec->av[0], &path_stat);
	if ((((path_stat.st_mode) & __S_IFMT) == (__S_IFDIR)))
	{
		ft_putstr_fd(exec->av[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		end(126);
	}
	av = get_copy_with_malloc(exec->av);
	garbage_collector();
	rl_clear_history();
	free(get_localvar()->pwd);
	free(get_localvar()->oldpwd);
	free(get_localvar()->default_path);
	execve(av[0], av, *get_env());
	perror(av[0]);
	ft_dblfree(av);
	return (exit(EXECUTION_FAILED), ft_dblfree(*get_env()), 1);
}

int	execute_cmd(t_execcmd *exec)
{
	int		status;
	pid_t	child_process;

	child_process = safe_fork();
	if (child_process == -1)
		return (ECHILD);
	*get_termsig() = 1;
	if (child_process == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execute(exec);
	}
	waitpid(child_process, &status, 0);
	*get_termsig() = 0;
	if ((((signed char)(((status) & 0x7f) + 1) >> 1) > 0) \
			&& ((status) & 0x7f) == SIGINT)
		return (CHILD_TERM_SIGINT);
	if ((((signed char)(((status) & 0x7f) + 1) >> 1) > 0) \
			&& ((status) & 0x7f) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (CHILD_TERM_SIGQUIT);
	}
	return (((status) & 0xff00) >> 8);
}

int	execute_builtin(t_execcmd *exec)
{
	if (ft_strncmp(exec->av[0], "cd", ft_strlen("cd") + 1) == 0)
		return (cd(exec->av));
	else if (ft_strncmp(exec->av[0], "echo", ft_strlen("echo") + 1) == 0)
		return (echo(exec->av));
	else if (ft_strncmp(exec->av[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (pwd());
	else if (ft_strncmp(exec->av[0], "export", ft_strlen("export") + 1) == 0)
		return (builtin_export(exec->av));
	else if (ft_strncmp(exec->av[0], "unset", ft_strlen("unset") + 1) == 0)
		return (unset(exec->av));
	else if (ft_strncmp(exec->av[0], "env", ft_strlen("env") + 1) == 0)
		return (builtin_env());
	else if (ft_strncmp(exec->av[0], "exit", ft_strlen("exit") + 1) == 0)
		return (builtin_exit(exec->av));
	return (-1);
}

int	execution(t_execcmd *exec)
{
	char	*_var;

	if (exec == NULL || exec->av[0] == NULL)
		return (0);
	_var = strjoin("_=", exec->av[ft_dblptrlen(exec->av) - 1]);
	exec->av = remove_invalid_variables(exec->av);
	exec->av = expand_cmd_variables(exec->av);
	update_variable(_var, *get_env(), 1);
	if (exec->av[0] == NULL)
		return (0);
	else if (exec->av[0][0] == '\0')
		return (ft_putstr_fd("Command '' not found\n", 2), 127);
	if (isbuiltin(exec->av[0]))
		return (execute_builtin(exec));
	else
		return (execute_cmd(exec));
}
