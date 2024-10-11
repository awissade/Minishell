/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 03:24:16 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/07 23:58:27 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define FILE_OPEN_FAILED 1

int	check_for_spaces(char *holder)
{
	int	jdx;

	jdx = -1;
	while (holder[++jdx])
	{
		if (ft_isspace(holder[jdx]))
			return (ft_putstr_fd("ambiguous redirect\n", 2), 0);
	}
	return (1);
}

int	check_filename(char *filename, int idx, char temp, int flag)
{
	char	*holder;
	int		jdx;

	while (filename[++idx])
	{
		if (ft_strchr("\"\'", filename[idx]) && flag == 0)
		{
			temp = filename[idx];
			flag = 1;
		}
		else if (filename[idx] == temp && flag == 1)
			flag = 0;
		else if (filename[idx] == '$' && flag == 0)
		{
			jdx = idx;
			holder = getvariable(filename, &jdx, get_localvar());
			if (holder == NULL)
				return (ft_putstr_fd("ambiguous redirect\n", 2), 0);
			if (check_for_spaces(holder) == 0)
				return (0);
		}
	}
	return (1);
}

char	*expand_file(char *filename)
{
	int		flag;
	int		idx;
	char	temp;

	flag = 0;
	idx = -1;
	temp = '\0';
	if (check_filename(filename, idx, temp, flag) == 0)
		return (NULL);
	filename = expand_element(filename);
	return (filename);
}

int	redirection(t_redircmd *redir)
{
	int	fd;
	int	status;
	int	stream_copy;

	if (redir == NULL)
		return (0);
	redir->file = expand_file(redir->file);
	if (redir->file == NULL)
		return (1);
	fd = open(redir->file, redir->mode, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (FILE_OPEN_FAILED);
	}
	stream_copy = dup(redir->fd);
	if (dup2(fd, redir->fd) == -1)
	{
		perror(redir->file);
		close(fd);
		return (FILE_OPEN_FAILED);
	}
	close(fd);
	status = runcmd(redir->cmd);
	return (dup2(stream_copy, redir->fd), close(stream_copy), status);
}
