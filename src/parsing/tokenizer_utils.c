/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:13:45 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 15:32:48 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoted_string_length(char *str)
{
	int		len;
	char	holder;

	len = 0;
	holder = *str;
	len++;
	while (str[len] != holder && str[len] != '\0')
		len++;
	if (str[len] != '\0')
		len++;
	while (ft_isspace(str[len]) == 0 && str[len] != '\0')
		len++;
	return (len);
}

int	control_operators_length(char *str)
{
	char	holder;
	int		len;

	if (str == NULL || *str == '\0')
		return (0);
	len = 0;
	holder = *str;
	while (str[len] == holder)
		len++;
	return (len);
}

int	subshell_block_length(char *string)
{
	int	idx;
	int	len;
	int	reserved;

	idx = 1;
	reserved = 0;
	len = 1;
	while (string[idx])
	{
		if (string[idx] == '(')
			reserved++;
		else if (string[idx] == ')' && reserved != 0)
			reserved--;
		else if (string[idx] == ')' && reserved == 0)
		{
			len++;
			break ;
		}
		len++;
		idx++;
	}
	return (len);
}
