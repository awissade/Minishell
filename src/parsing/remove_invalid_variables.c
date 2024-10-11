/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_invalid_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:38:23 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/04 21:43:10 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_argument(char **av, int remove_idx)
{
	int		idx;
	int		jdx;

	idx = 0;
	jdx = 0;
	while (av[idx])
	{
		if (idx == remove_idx)
		{
			idx++;
			continue ;
		}
		av[jdx] = av[idx];
		idx++;
		jdx++;
	}
	av[jdx] = NULL;
}

char	**remove_invalid_variables(char **av)
{
	int		idx;
	char	*holder;

	idx = 0;
	while (av[idx])
	{
		if (av[idx][0] == '$')
		{
			holder = expand_element(av[idx]);
			if (holder != NULL && holder[0] == '\0')
				remove_argument(av, idx);
		}
		idx++;
	}
	return (av);
}
