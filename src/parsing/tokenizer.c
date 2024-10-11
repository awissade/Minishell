/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:00:55 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/09 11:36:21 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenlen(char *commandline)
{
	if (ft_strchr("|&<>", *commandline))
		return (control_operators_length(commandline));
	else if (*commandline == '(')
		return (subshell_block_length(commandline));
	else
		return (string_length(commandline));
}

void	get_token(char **commandline_ptr, t_token *token)
{
	int		len;
	char	*commandline;

	commandline = *commandline_ptr;
	if (*commandline == '>' && *(commandline + 1) == '>')
		token->type = '+';
	else if (*commandline == '>')
		token->type = '>';
	else if (*commandline == '<' && *(commandline + 1) == '<')
		token->type = 'h';
	else if (*commandline == '<')
		token->type = '<';
	else if (*commandline == '|' && *(commandline + 1) == '|')
		token->type = 'o';
	else if (*commandline == '|')
		token->type = '|';
	else if (*commandline == '&' && *(commandline + 1) == '&')
		token->type = 'n';
	else if (*commandline == '(')
		token->type = '(';
	else
		token->type = 'a';
	len = tokenlen(commandline);
	token->content = get_token_content(commandline, len);
	advance_pointer(commandline_ptr, len);
}

t_token	*last_token(t_token *tokens_head)
{
	if (tokens_head == NULL)
		return (NULL);
	while (tokens_head->next != NULL)
		tokens_head = tokens_head->next;
	return (tokens_head);
}

void	addback_token(t_token **tokens_head, t_token *new_token)
{
	t_token	*temp;

	if (tokens_head == NULL || new_token == NULL)
		return ;
	if (*tokens_head == NULL)
		*tokens_head = new_token;
	else
	{
		temp = last_token(*tokens_head);
		temp->next = new_token;
		new_token->prev = temp;
	}
}

t_token	*tokenizer(char *commandline)
{
	t_token	*tokens_head;
	t_token	*token;

	tokens_head = NULL;
	while (*commandline != '\0' && *commandline != '\n')
	{
		token = safe_alloc(sizeof(t_token));
		ft_bzero((void *)token, sizeof(t_token));
		skip_spaces(&commandline);
		get_token(&commandline, token);
		addback_token(&tokens_head, token);
		skip_spaces(&commandline);
	}
	return (tokens_head);
}
