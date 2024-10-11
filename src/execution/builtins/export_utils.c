/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awissade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:34:16 by awissade          #+#    #+#             */
/*   Updated: 2024/07/30 15:29:08 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_var(char *var)
{
	int	jdx;
	int	flag;

	jdx = 0;
	flag = 0;
	while (var[jdx])
	{
		ft_putchar_fd(var[jdx], 1);
		if (var[jdx] == '=' && flag == 0)
		{
			ft_putchar_fd('\"', 1);
			flag = 1;
		}
		jdx++;
	}
	return (flag);
}

void	print_env(char **env)
{
	int	idx;
	int	flag;

	idx = 0;
	while (env[idx])
	{
		if (compare_variables(env[idx], "_=") == 0)
		{
			idx++;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		flag = print_var(env[idx]);
		if (flag == 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		idx++;
	}
	ft_dblfree(env);
}

char	**split_var(char *str, char *sep)
{
	int		idx;
	int		jdx;
	int		kdx;
	char	**args;

	idx = -1;
	args = safe_alloc(sizeof(char *) * 3);
	while (str[++idx])
	{
		if (str[idx] == sep[0])
		{
			jdx = idx;
			kdx = 0;
			while (str[jdx] == sep[kdx] && sep[kdx] && str[jdx])
				increment_indexes(&jdx, &kdx);
			if (sep[kdx] == '\0')
			{
				args[0] = ft_strndup(str, idx);
				args[1] = ft_strndup(&str[jdx], ft_strlen(str) - jdx);
				break ;
			}
		}
	}
	return (args[2] = NULL, args);
}

int	name_isvalid(char *var)
{
	char	*varname;
	int		idx;
	int		temp1;
	int		temp2;

	temp1 = cm_strstr(var, "+=");
	temp2 = cm_strstr(var, "=");
	if ((temp1 < temp2 && temp1 >= 0) || (temp1 >= 0 && temp2 < 0))
		varname = split_var(var, "+=")[0];
	else if ((temp2 < temp1 && temp2 >= 0) || (temp2 >= 0 && temp1 < 0))
		varname = split_var(var, "=")[0];
	else
		varname = var;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (0);
	idx = 0;
	while (varname[idx])
	{
		if (valid_char(varname[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}

void	increment_indexes(int *var1, int *var2)
{
	*var1 += 1;
	*var2 += 1;
}
