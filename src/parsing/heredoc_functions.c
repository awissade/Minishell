/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:10:49 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/03 05:24:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_input_in_tempfile(char *limiter, int fd)
{
	char	*line;
	char	*holder;

	if (ft_strchr(limiter, '\"') || ft_strchr(limiter, '\''))
		limiter = remove_quotes(limiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			return ;
		}
		holder = cm_strdup(line);
		free(line);
		write(fd, holder, ft_strlen(holder));
		write(fd, "\n", 1);
	}
}

void	child_process(int *fds, char *limiter)
{
	close(fds[1]);
	put_input_in_tempfile(limiter, fds[0]);
	close(fds[0]);
	end(EXIT_SUCCESS);
}

int	check_childprocess_term_signal(int status)
{
	if ((((status) & 0xff00) >> 8) == 130)
	{
		get_localvar()->exit_status = 130;
		return (1);
	}
	return (0);
}

char	*get_heredoc_input_as_string(int fd, char *limiter)
{
	char	*input;
	char	*line;
	int		flag;

	input = cm_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		input = strjoin(input, line);
	}
	flag = 0;
	if (ft_strchr(limiter, '\"') || ft_strchr(limiter, '\''))
		flag = 1;
	if (flag == 0)
		input = expand(input);
	return (input);
}

char	*get_heredoc_input(char *limiter)
{
	int		fds[2];
	int		status;
	char	*input;
	pid_t	child_pid;

	fds[0] = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY, 0777);
	fds[1] = open("/tmp/heredoc.tmp", O_RDONLY, 0777);
	unlink("/tmp/heredoc.tmp");
	*get_heredoc_termsig() = 1;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (child_pid == 0)
		child_process(fds, limiter);
	*get_heredoc_termsig() = 2;
	waitpid(child_pid, &status, 0);
	*get_heredoc_termsig() = 0;
	close(fds[0]);
	if (check_childprocess_term_signal(status))
		return (NULL);
	input = get_heredoc_input_as_string(fds[1], limiter);
	return (close(fds[1]), input);
}
