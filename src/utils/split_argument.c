/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:39:56 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 10:42:28 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *arg, int *idx)
{
	char	holder;

	holder = arg[(*idx)++];
	while (arg[(*idx)] != holder && arg[(*idx)])
		(*idx)++;
	if (arg[(*idx)] == holder)
		(*idx)++;
}

char	**split_argument(char *arg, int numof_args)
{
	char	**args;
	int		idx;
	int		jdx;
	int		kdx;

	idx = 0;
	kdx = 0;
	args = safe_alloc(sizeof(char *) * (numof_args + 1));
	while (arg[idx])
	{
		while (ft_isspace(arg[idx]))
			idx++;
		jdx = idx;
		while (!ft_isspace(arg[idx]) && arg[idx])
		{
			if (ft_strchr("\"\'", arg[idx]) \
				&& ((idx != 0 && arg[idx - 1] != 1) || idx == 0))
				skip_quotes(arg, &idx);
			else
				idx++;
		}
		if (idx > jdx)
			args[kdx++] = ft_strndup(arg + jdx, idx - jdx);
	}
	return (args[kdx] = NULL, args);
}
