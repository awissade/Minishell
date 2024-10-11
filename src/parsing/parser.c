/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:09:09 by ajawad            #+#    #+#             */
/*   Updated: 2024/10/09 15:52:56 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_exec(t_token *tokens_ptr)
{
	t_cmd	*exec;

	exec = execcmd(get_command_args(tokens_ptr));
	return (exec);
}

t_cmd	*parse_subshell_block(t_token *tokens_ptr)
{
	t_cmd	*cmd;
	t_token	*token;

	token = peek(tokens_ptr, '(');
	if (token)
		cmd = subshell_block(tokens_ptr->content);
	else
		cmd = parse_exec(tokens_ptr);
	return (cmd);
}

t_cmd	*parse_logop(t_token *tokens_ptr)
{
	t_cmd	*logop;
	t_token	*token;

	token = peek_for_logop(tokens_ptr);
	if (token && token->type == 'n')
	{
		token->prev->next = NULL;
		token->next->prev = NULL;
		logop = logopcmd(1, parse_logop(tokens_ptr), parse_logop(token->next));
	}
	else if (token && token->type == 'o')
	{
		token->prev->next = NULL;
		token->next->prev = NULL;
		logop = logopcmd(0, parse_logop(tokens_ptr), parse_logop(token->next));
	}
	else
		logop = parse_pipe(tokens_ptr);
	return (logop);
}

t_cmd	*parse_pipe(t_token *tokens_ptr)
{
	t_cmd	*pipe;
	t_token	*token;

	token = peek(tokens_ptr, '|');
	if (token != NULL)
	{
		token->prev->next = NULL;
		token->next->prev = NULL;
		pipe = pipecmd(parse_redir(tokens_ptr), parse_pipe(token->next));
	}
	else
		pipe = parse_redir(tokens_ptr);
	return (pipe);
}

t_cmd	*parse_cmd(t_token *token_ptr)
{
	t_cmd	*cmd;

	cmd = parse_logop(token_ptr);
	return (cmd);
}
