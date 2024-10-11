/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 05:27:59 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 15:43:13 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_dollar(char *arg, int idx)
{
	if (arg[idx] == '$' && (!ft_isalnum(arg[idx + 1]) && arg[idx + 1] != '?'))
		return (1);
	return (0);
}

int	nonquoted_string_length(char *arg, int idx)
{
	int	len;

	len = idx;
	while (!ft_strchr("\"\'", arg[len]) && arg[len])
		len++;
	return (len);
}

char	*add_quotes(char *str)
{
	char	*quoted_str;
	int		idx;
	int		jdx;

	quoted_str = safe_alloc(sizeof(char) * (ft_strlen(str) + 2 + 1));
	jdx = 0;
	quoted_str[jdx++] = '\"';
	idx = 0;
	while (str[idx])
	{
		quoted_str[jdx] = str[idx];
		idx++;
		jdx++;
	}
	quoted_str[jdx++] = '\"';
	quoted_str[jdx] = '\0';
	return (quoted_str);
}

char	*getvariable_clean(char *arg, char *newarg, int *idx, int flag)
{
	char	*temp;

	temp = getvariable(arg, idx, get_localvar());
	if (temp != NULL)
	{
		temp = remove_trailing_whitspaces(temp);
		if (flag == 1)
			temp = add_quotes(temp);
		newarg = strjoin(newarg, temp);
	}
	return (newarg);
}
