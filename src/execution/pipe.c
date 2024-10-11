/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:56:55 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 18:37:24 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error(char *err_msg)
{
	perror(err_msg);
	return (EPIPE);
}

void	child_process1(int *ends, t_pipecmd *pipe_symbol)
{
	signal(SIGQUIT, SIG_DFL);
	*inparent() = 0;
	close(ends[0]);
	dup2(ends[1], STDOUT_FILENO);
	close(ends[1]);
	end(runcmd(pipe_symbol->left));
}

void	child_process2(int *ends, t_pipecmd *pipe_symbol)
{
	signal(SIGQUIT, SIG_DFL);
	*inparent() = 0;
	close(ends[1]);
	dup2(ends[0], STDIN_FILENO);
	close(ends[0]);
	end(runcmd(pipe_symbol->right));
}

int	wait_and_catchsignal(int *status, pid_t child1_pid, pid_t child2_pid)
{
	waitpid(child1_pid, status, 0);
	waitpid(child2_pid, status, 0);
	if ((((signed char)(((*status) & 0x7f) + 1) >> 1) > 0) \
			&& ((*status) & 0x7f) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (1);
	}
	return (0);
}

int	piping(t_pipecmd *pipe_symbol)
{
	int		ends[2];
	pid_t	child1_pid;
	pid_t	child2_pid;
	int		status;

	if (pipe_symbol == NULL)
		return (0);
	if (pipe(ends) == -1)
		return (error("pipe"));
	child1_pid = safe_fork();
	if (child1_pid == -1)
		return (ECHILD);
	if (child1_pid == 0)
		child_process1(ends, pipe_symbol);
	child2_pid = safe_fork();
	if (child2_pid == -1)
		return (ECHILD);
	if (child2_pid == 0)
		child_process2(ends, pipe_symbol);
	*isreturning() = 1;
	close(ends[0]);
	close(ends[1]);
	if (wait_and_catchsignal(&status, child1_pid, child2_pid) == 1)
		return (131);
	return (((status) & 0xff00) >> 8);
}
