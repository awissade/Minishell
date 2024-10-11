/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:02:25 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 16:04:10 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_numof_args(char *str)
{
	int		idx;
	int		numof_args;
	char	holder;

	idx = -1;
	numof_args = 0;
	while (str[++idx])
	{
		if (ft_strchr("\"\'", str[idx]) \
			&& ((idx != 0 && str[idx - 1] != 1) || idx == 0))
		{
			holder = str[idx++];
			while (str[idx] != holder && str[idx])
				idx++;
			if (str[idx] == '\0')
			{
				numof_args++;
				break ;
			}
		}
		if (!ft_isspace(str[idx]) \
			&& (ft_isspace(str[idx + 1]) || str[idx + 1] == '\0'))
			numof_args++;
	}
	return (numof_args);
}

int	calculate_new_lenght(char *str)
{
	int	idx;
	int	len;

	idx = 0;
	len = 0;
	while (str[idx])
	{
		if (str[idx] == 1 && ft_strchr("\"\'", str[idx + 1]))
		{
			idx++;
			continue ;
		}
		len++;
		idx++;
	}
	return (len);
}

char	*remove_escape_characters(char *str)
{
	int		idx;
	int		jdx;
	int		len;
	char	*newstr;

	len = calculate_new_lenght(str);
	newstr = safe_alloc(sizeof(char) * (len + 1));
	idx = 0;
	jdx = 0;
	while (str[idx])
	{
		if (str[idx] == 1 && ft_strchr("\"\'", str[idx + 1]))
		{
			idx++;
			continue ;
		}
		newstr[jdx] = str[idx];
		jdx++;
		idx++;
	}
	newstr[jdx] = '\0';
	return (newstr);
}

char	**add_args(char **av, char *arg, int numof_args)
{
	char	**newav;
	char	**args;
	int		idx;
	int		jdx;

	newav = safe_alloc(sizeof(char *) * (ft_dblptrlen(av) + numof_args + 1));
	idx = -1;
	while (av[++idx])
		newav[idx] = av[idx];
	args = split_argument(arg, numof_args);
	jdx = 0;
	while (args[jdx])
	{
		newav[idx] = remove_quotes(args[jdx]);
		idx++;
		jdx++;
	}
	newav[idx] = NULL;
	return (newav);
}

char	**expand_cmd_variables(char **av)
{
	int		idx;
	char	*holder;
	char	**newav;

	newav = safe_alloc(sizeof(char *) * 1);
	newav[0] = NULL;
	idx = 0;
	while (av[idx])
	{
		holder = expand(av[idx]);
		newav = add_args(newav, holder, calc_numof_args(holder));
		idx++;
	}
	return (newav);
}
