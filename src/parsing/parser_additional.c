/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_additional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:15:37 by ajawad            #+#    #+#             */
/*   Updated: 2024/10/09 15:53:32 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*peek_for_logop(t_token *tokens_ptr)
{
	while (tokens_ptr->next)
		tokens_ptr = tokens_ptr->next;
	while (tokens_ptr)
	{
		if (ft_strchr("no", tokens_ptr->type))
			return (tokens_ptr);
		tokens_ptr = tokens_ptr->prev;
	}
	return (NULL);
}

t_cmd	*handle_redir(t_token *tokens_ptr, char type, int mode, int fd)
{
	t_cmd	*redir;
	t_token	*token;

	token = peek(tokens_ptr, type);
	token->type = 'p';
	token->next->type = 'p';
	redir = redircmd(token->next->content, mode, fd, parse_redir(tokens_ptr));
	return (redir);
}

t_token	*peek_for_redir(t_token *tokens_ptr)
{
	while (tokens_ptr)
	{
		if (ft_strchr("><+h", tokens_ptr->type))
			return (tokens_ptr);
		tokens_ptr = tokens_ptr->next;
	}
	return (NULL);
}

t_cmd	*parse_redir(t_token *tokens_ptr)
{
	t_cmd	*redir;
	t_token	*token;

	redir = NULL;
	token = peek_for_redir(tokens_ptr);
	if (token == NULL)
		redir = parse_subshell_block(tokens_ptr);
	else if (token->type == '<')
		redir = handle_redir(tokens_ptr, '<', O_RDONLY, 0);
	else if (token->type == '>')
		redir = handle_redir(tokens_ptr, '>', O_CREAT | O_WRONLY | O_TRUNC, 1);
	else if (token->type == 'h')
	{
		token->type = 'p';
		token->next->type = 'p';
		redir = heredoccmd(token->next->content, parse_redir(tokens_ptr));
	}
	else if (token->type == '+')
		redir = handle_redir(tokens_ptr, '+', O_CREAT | O_WRONLY | O_APPEND, 1);
	return (redir);
}
