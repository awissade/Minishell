/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awissade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:01:19 by awissade          #+#    #+#             */
/*   Updated: 2024/08/08 16:15:32 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_variables(char *newarg, char *arg, int *idx, int flag)
{
	char	*temp;

	temp = getvariable(arg, idx, get_localvar());
	if (temp != NULL)
	{
		newarg = strjoin(newarg, temp);
		if (flag == 1)
			newarg = add_quotes(newarg);
	}
	return (newarg);
}

int	is_special_dollar_sign(char *arg, int idx)
{
	if (arg[idx] == '$' && (((!ft_isalnum(arg[idx + 1]) && arg[idx + 1] != '?') \
		&& !ft_strchr("\"\'", arg[idx + 1])) || arg[idx + 1] == '\0'))
		return (1);
	return (0);
}

int	block_length(char *arg)
{
	int		len;
	char	holder;

	len = 0;
	holder = arg[0];
	len++;
	while (arg[len] != holder && arg[len])
		len++;
	if (arg[len] == holder)
		len++;
	return (len);
}

int	isdynamic_assignement(char *arg)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (arg[idx] != '=' && arg[idx])
	{
		if (arg[idx] == '$')
			flag = 1;
		idx++;
	}
	if (arg[idx] == '=' && flag == 1)
		return (1);
	return (0);
}

char	*getenv_locally(char *variable_name, t_localvar *localvar)
{
	char	*variable_value;
	char	*holder;

	variable_value = NULL;
	if (!ft_strncmp(variable_name, "PWD", ft_strlen("PWD")))
		variable_value = localvar->pwd;
	else if (!ft_strncmp(variable_name, "OLDPWD", ft_strlen("OLDPWD")))
		variable_value = localvar->oldpwd;
	else if (!ft_strncmp(variable_name, "?", ft_strlen("?")))
	{
		holder = cm_itoa(localvar->exit_status);
		variable_value = cm_strdup(holder);
	}
	return (variable_value);
}
