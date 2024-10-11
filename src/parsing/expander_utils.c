/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:41:37 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 03:30:40 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd_or_oldpwd(char *variable_name, int active)
{
	if (active == 1 && (!ft_strncmp(variable_name, "PWD", ft_strlen("PWD") + 1)
			|| !ft_strncmp(variable_name, "OLDPWD", ft_strlen("OLDPWD") + 1)))
		return (1);
	return (0);
}

int	calc_len(char *arg, int start)
{
	int	len;

	if (arg[start] == '?')
		return (1);
	len = start;
	while (ft_isalnum(arg[len]) || arg[len] == '_')
		len++;
	len = len - start;
	return (len);
}

int	len_with_escape(char *var)
{
	int	len;
	int	numof_escapes;

	len = -1;
	numof_escapes = 0;
	while (var[++len])
	{
		if (ft_strchr("\"\'", var[len]))
			numof_escapes++;
	}
	return (len + numof_escapes);
}

char	*add_escape_charachter(char *var)
{
	int		idx;
	int		jdx;
	char	*newvar;

	if (var == NULL)
		return (NULL);
	newvar = safe_alloc(sizeof(char) * (len_with_escape(var) + 1));
	idx = -1;
	jdx = 0;
	while (var[++idx])
	{
		if (ft_strchr("\"\'", var[idx]))
			newvar[jdx++] = 1;
		newvar[jdx] = var[idx];
		jdx++;
	}
	return (newvar[jdx] = '\0', newvar);
}

char	*getvariable(char *arg, int *start, t_localvar *localvar)
{
	int		len;
	char	*variable_name;
	char	*variable_value;

	(*start)++;
	if (arg[(*start)] == '{')
		(*start)++;
	else if (arg[(*start)] == '\"' || arg[(*start)] == '\'')
		return (return_nameof_variable(arg, start));
	len = calc_len(arg, *start);
	variable_name = safe_alloc(sizeof(char) * (len + 1));
	ft_strlcpy(variable_name, &arg[(*start)], (len + 1));
	while (len-- > 0)
		(*start)++;
	if (arg[(*start)] == '}')
		(*start)++;
	if (!compare_variables(variable_name, "?"))
		variable_value = getenv_locally(variable_name, localvar);
	else if (is_pwd_or_oldpwd(variable_name, localvar->active))
		variable_value = getenv_locally(variable_name, localvar);
	else
		variable_value = ft_getenv(variable_name);
	return (add_escape_charachter(variable_value));
}
