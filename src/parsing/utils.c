/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:04:56 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/27 14:04:10 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SYNTAX_ERROR 2

char	*char_to_string(char character)
{
	char	*string;

	string = safe_alloc(sizeof(char) * 2);
	string[0] = character;
	string[1] = '\0';
	return (string);
}

char	*get_type_element(char type)
{
	if (type == 'n')
		return (cm_strdup("&&"));
	else if (type == 'o')
		return (cm_strdup("||"));
	else if (type == '|')
		return (cm_strdup("|"));
	else if (type == '>')
		return (cm_strdup(">"));
	else if (type == '<')
		return (cm_strdup("<"));
	else if (type == '+')
		return (cm_strdup(">>"));
	else if (type == 'h')
		return (cm_strdup("<<"));
	else if (type == '(')
		return (cm_strdup("("));
	else
		return (NULL);
}

int	syntax_error(int flag, char *token)
{
	ft_putstr_fd("syntax error: ", 2);
	if (flag == UNCLOSED_QUOTES)
		ft_putstr_fd("unclosed quotes ", 2);
	if (flag == UNEXPECTED)
		ft_putstr_fd("unexpected token ", 2);
	ft_putstr_fd(token, 2);
	ft_putchar_fd('\n', 2);
	return (SYNTAX_ERROR);
}
