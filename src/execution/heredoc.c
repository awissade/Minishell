/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 03:46:49 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/01 02:16:02 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_stdin_back(int stdin_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}

int	make_temp_heredocfile(char *input)
{
	int	fds[2];

	fds[0] = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY, 0777);
	fds[1] = open("/tmp/heredoc.tmp", O_RDONLY, 0777);
	unlink("/tmp/heredoc.tmp");
	write(fds[0], input, ft_strlen(input));
	close(fds[0]);
	return (fds[1]);
}

int	heredoc(t_heredoccmd *heredoc)
{
	int		stdin_copy;
	int		status;
	int		fd;

	if (heredoc == NULL)
		return (0);
	fd = make_temp_heredocfile(heredoc->input);
	stdin_copy = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (EBADF);
	status = runcmd(heredoc->cmd);
	get_stdin_back(stdin_copy);
	close(fd);
	return (status);
}
