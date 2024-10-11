/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:59:21 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 13:25:29 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_doublyquoted_string(char *arg, char *newarg, int *idx, \
		char *arr)
{
	int		len;
	int		flag;

	flag = 0;
	len = block_length(&arg[*idx]) + *idx;
	while (*idx < len)
	{
		if (arg[*idx] == '=')
			flag = 1;
		else if (ft_isspace(arg[*idx]))
			flag = 0;
		if (is_special_dollar(arg, *idx))
		{
			newarg = strjoin(newarg, "$");
			(*idx)++;
		}
		else if (arg[*idx] == '$')
			newarg = handle_variables(newarg, arg, idx, flag);
		else
		{
			arr[0] = arg[(*idx)++];
			newarg = strjoin(newarg, arr);
		}
	}
	return (newarg);
}

char	*handle_singlyquoted_string(char *arg, char *newarg, int *idx)
{
	char	*temp;
	int		len;
	int		jdx;

	len = block_length(&arg[*idx]);
	temp = safe_alloc(sizeof(char) * (len + 1));
	len = len + *idx;
	jdx = 0;
	while (*idx < len)
	{
		temp[jdx] = arg[*idx];
		(*idx)++;
		jdx++;
	}
	temp[jdx] = '\0';
	newarg = strjoin(newarg, temp);
	return (newarg);
}

char	*handle_nonquoted_string(char *arg, char *newarg, int *idx, char *arr)
{
	int		len;
	int		flag;

	flag = 0;
	len = nonquoted_string_length(arg, *idx);
	while (*idx < len)
	{
		if (arg[*idx] == '=' && isdynamic_assignement(arg) == 0)
			flag = 1;
		else if (ft_isspace(arg[*idx]))
			flag = 0;
		if (is_special_dollar_sign(arg, *idx))
		{
			newarg = strjoin(newarg, "$");
			(*idx)++;
		}
		else if (arg[*idx] == '$')
			newarg = getvariable_clean(arg, newarg, idx, flag);
		else
		{
			arr[0] = arg[(*idx)++];
			newarg = strjoin(newarg, arr);
		}
	}
	return (newarg);
}

char	*expand(char *arg)
{
	int		idx;
	char	*newarg;
	char	arr[2];

	idx = 0;
	arr[1] = '\0';
	newarg = cm_strdup("");
	while (arg[idx])
	{
		if (arg[idx] == '\"')
			newarg = handle_doublyquoted_string(arg, newarg, &idx, arr);
		else if (arg[idx] == '\'')
			newarg = handle_singlyquoted_string(arg, newarg, &idx);
		else
			newarg = handle_nonquoted_string(arg, newarg, &idx, arr);
	}
	return (newarg);
}

char	*expand_element(char *arg)
{
	char	*newarg;

	newarg = expand(arg);
	newarg = remove_quotes(newarg);
	return (newarg);
}
