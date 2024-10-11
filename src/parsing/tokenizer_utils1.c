/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awissade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:31:51 by awissade          #+#    #+#             */
/*   Updated: 2024/08/09 11:42:05 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_content(char *commandline, int len)
{
	int		start;

	start = 0;
	return (substr(commandline, start, len));
}

void	advance_pointer(char **ptr, int len)
{
	while (len-- > 0)
		(*ptr)++;
}

int	string_length(char	*commandline)
{
	int		len;
	char	holder;

	len = 0;
	while (!ft_strchr("|&<>\n", commandline[len]) \
			&& !ft_isspace(commandline[len]) && commandline[len])
	{
		if (ft_strchr("\"\'", commandline[len]))
		{
			holder = commandline[len];
			len++;
			while (commandline[len] != holder && commandline[len])
				len++;
			if (commandline[len] == holder)
				len++;
		}
		else
			len++;
	}
	return (len);
}
