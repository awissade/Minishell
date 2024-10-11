/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:51:17 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/22 19:09:33 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*pipe;

	pipe = safe_alloc(sizeof(t_pipecmd));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

t_cmd	*logopcmd(int mode, t_cmd *left, t_cmd *right)
{
	t_logopcmd	*logop;

	logop = safe_alloc(sizeof(t_logopcmd));
	logop->type = LOGOP;
	logop->mode = mode;
	logop->left = left;
	logop->right = right;
	return ((t_cmd *)logop);
}

t_cmd	*redircmd(char *file, int mode, int fd, t_cmd *cmd)
{
	t_redircmd	*redir;

	redir = safe_alloc(sizeof(t_redircmd));
	redir->type = REDIR;
	redir->file = file;
	redir->mode = mode;
	redir->fd = fd;
	redir->cmd = cmd;
	return ((t_cmd *)redir);
}

t_cmd	*heredoccmd(char *input, t_cmd *cmd)
{
	t_heredoccmd	*heredoc;

	heredoc = safe_alloc(sizeof(t_heredoccmd));
	heredoc->type = HEREDOC;
	heredoc->input = input;
	heredoc->cmd = cmd;
	return ((t_cmd *)heredoc);
}

t_cmd	*execcmd(char **av)
{
	t_execcmd	*cmd;

	cmd = safe_alloc(sizeof(t_execcmd));
	cmd->type = EXEC;
	cmd->av = av;
	return ((t_cmd *)cmd);
}
