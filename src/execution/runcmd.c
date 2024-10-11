/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:54:22 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/29 10:56:52 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	runcmd(t_cmd *cmd)
{
	if (cmd->type == LOGOP)
		return (logop((t_logopcmd *)cmd));
	else if (cmd->type == PIPE)
		return (piping((t_pipecmd *)cmd));
	else if (cmd->type == HEREDOC)
		return (heredoc((t_heredoccmd *)cmd));
	else if (cmd->type == REDIR)
		return (redirection((t_redircmd *)cmd));
	else if (cmd->type == SUBSHELL)
		return (execute_subshell_block((t_subshellcmd *)cmd));
	else if (cmd->type == EXEC)
		return (execution((t_execcmd *)cmd));
	else
		return (EXIT_SUCCESS);
}
