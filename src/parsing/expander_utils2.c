/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:40:57 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/09 14:52:46 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_nameof_variable(char *arg, int *start)
{
	int		len;
	int		start_idx;
	char	*newarg;

	len = 0;
	(*start)++;
	start_idx = *start;
	while (arg[(*start)] != '\"' && arg[(*start)] != '\'' && arg[(*start)])
	{
		len++;
		(*start)++;
	}
	if (arg[(*start)] == '\"' || arg[(*start)] == '\'')
		(*start)++;
	newarg = substr(arg, start_idx, len);
	newarg = expand(newarg);
	return (newarg);
}

int	len_without_quotes(char *str)
{
	int		idx;
	int		len;
	int		flag;
	char	holder;

	len = 0;
	idx = 0;
	flag = 0;
	holder = '\0';
	while (str[idx])
	{
		if (ft_strchr("\"\'", str[idx]) && flag == 0 \
			&& ((idx != 0 && str[idx - 1] != 1) || idx == 0))
		{
			holder = str[idx];
			flag = 1;
		}
		else if (str[idx] == holder \
				&& ((idx != 0 && str[idx - 1] != 1) || idx == 0))
			flag = 0;
		else if (str[idx] != holder)
			len++;
		idx++;
	}
	return (len);
}

char	*core_remove_quotes(char *str, char *newstr, int idx1, int idx2)
{
	int		flag;
	char	holder;

	flag = 0;
	holder = '\0';
	while (str[++idx1])
	{
		if ((str[idx1] == '\"' || str[idx1] == '\'') && flag == 0 \
			&& ((idx1 != 0 && str[idx1 - 1] != 1) || idx1 == 0))
		{
			holder = str[idx1];
			flag = 1;
		}
		else if (str[idx1] == holder \
				&& ((idx1 != 0 && str[idx1 - 1] != 1) || idx1 == 0))
			flag = 0;
		else if (str[idx1] == 1)
			continue ;
		else
			newstr[idx2++] = str[idx1];
	}
	newstr[idx2] = '\0';
	return (newstr);
}

char	*remove_quotes(char *str)
{
	int		idx1;
	int		idx2;
	char	*newstr;

	if (str == NULL)
		return (cm_strdup(""));
	newstr = safe_alloc(sizeof(char) * (len_without_quotes(str) + 1));
	idx1 = -1;
	idx2 = 0;
	return (core_remove_quotes(str, newstr, idx1, idx2));
}
