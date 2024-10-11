/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awissade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:50:11 by awissade          #+#    #+#             */
/*   Updated: 2024/07/30 15:30:13 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_variable(char *var, char **env)
{
	char	**newenv;
	int		idx;

	newenv = malloc(sizeof(char *) * (ft_dblptrlen(env) + 2));
	if (newenv == NULL)
	{
		perror("Fatal");
		panic(12);
	}
	idx = 0;
	while (env && env[idx])
	{
		newenv[idx] = ft_strdup(env[idx]);
		idx++;
	}
	newenv[idx] = ft_strdup(var);
	newenv[++idx] = NULL;
	ft_dblfree(env);
	*get_env() = newenv;
}

void	concat_to_var(char *var, char **env)
{
	int		idx;
	char	**vargs;
	char	*var_name;
	char	*holder;
	int		flag;

	idx = -1;
	flag = 0;
	vargs = split_var(var, "+=");
	var_name = strjoin(vargs[0], "=");
	if (vargs[1][0] == '\0')
		flag = 1;
	while (env[++idx])
	{
		if (compare_variables(env[idx], var_name) == 0)
		{
			if (flag == 1)
				return ;
			holder = env[idx];
			env[idx] = ft_strjoin(env[idx], vargs[1]);
			free(holder);
			return ;
		}
	}
	add_variable(strjoin(var_name, vargs[1]), env);
}

void	update_variable(char *var, char **env, int var_with_value)
{
	int		idx;
	char	*varname;

	idx = 0;
	varname = var;
	while (env[idx])
	{
		if (compare_variables(env[idx], varname) == 0)
		{
			if (var_with_value == 0)
				return ;
			free(env[idx]);
			env[idx] = ft_strdup(var);
			return ;
		}
		idx++;
	}
	add_variable(var, env);
}

int	export_variable(char *var)
{
	int	temp1;
	int	temp2;

	if (name_isvalid(var) == 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": is not a valid identifier\n", 2);
		return (1);
	}
	temp1 = cm_strstr(var, "+=");
	temp2 = cm_strstr(var, "=");
	if ((temp1 < temp2 && temp1 >= 0) || (temp1 >= 0 && temp2 < 0))
		concat_to_var(var, *get_env());
	else if ((temp2 < temp1 && temp2 >= 0) || (temp2 >= 0 && temp1 < 0))
		update_variable(var, *get_env(), 1);
	else
		update_variable(var, *get_env(), 0);
	return (0);
}

int	valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' \
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
