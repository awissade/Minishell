/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:07:41 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/09 11:21:29 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *content)
{
	char	*ptr;

	while (*content)
	{
		if (ft_strchr("\"\'", *content))
		{
			ptr = ft_strchr(content, *content);
			ptr = ft_strchr(ptr + 1, *content);
			if (ptr == NULL)
				return (syntax_error(UNCLOSED_QUOTES,
						char_to_string(*content)));
			content = ptr;
		}
		content++;
	}
	return (0);
}

int	check_placement(t_token *token)
{
	if (ft_strchr("<>h+", token->type))
	{
		if (token->next == NULL)
			return (syntax_error(UNEXPECTED, get_type_element(token->type)));
		if (token->next->type != 'a')
			return (syntax_error(UNEXPECTED,
					get_type_element(token->next->type)));
	}
	else if (ft_strchr("|no", token->type))
	{
		if (token->prev == NULL || token->next == NULL)
			return (syntax_error(UNEXPECTED, get_type_element(token->type)));
		if (ft_strchr("|no", token->next->type))
			return (syntax_error(UNEXPECTED, \
					get_type_element(token->next->type)));
	}
	else if (token->type == '(' && token->next != NULL)
	{
		if (token->next->type == 'a' && ft_strncmp(token->next->content, \
				"\n", ft_strlen(token->next->content)))
			return (syntax_error(UNEXPECTED, token->next->content));
		else if (token->next->type == '(')
			return (syntax_error(UNEXPECTED, "("));
	}
	return (0);
}

int	check_closing_parentheses(char *str)
{
	int	idx;

	if (str[0] == '\"' || str[0] == '\'')
		return (0);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == ')')
			return (syntax_error(UNEXPECTED, ")"));
		idx++;
	}
	return (0);
}

int	check_token(t_token *token)
{
	if (ft_strchr("no+h", token->type) && ft_strlen(token->content) != 2)
		return (syntax_error(UNEXPECTED, get_type_element(token->type)));
	return (0);
}

int	validator(t_token *tokens)
{
	int		status;
	t_token	*temp;

	status = 0;
	temp = tokens;
	while (tokens)
	{
		if (tokens->type == 'a')
			status = check_following(tokens);
		if (ft_strchr("no+h", tokens->type) && status == 0)
			status = check_token(tokens);
		if (tokens->type == 'a' && status == 0)
			status = check_quotes(tokens->content);
		if (tokens->type == 'a' && status == 0)
			status = check_closing_parentheses(tokens->content);
		if (ft_strchr("<>h+|no(", tokens->type) && status == 0)
			status = check_placement(tokens);
		if (status != 0)
			return (status);
		tokens = tokens->next;
	}
	check_numof_heredocs(temp);
	return (0);
}
