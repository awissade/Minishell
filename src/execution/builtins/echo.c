/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:51:31 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 15:02:08 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char **av, int *idx)
{
	int	flag;
	int	jdx;

	jdx = 0;
	flag = 0;
	while (av[*idx] && av[*idx][0] == '-')
	{
		jdx = 1;
		while (av[*idx][jdx])
		{
			if (av[*idx][jdx] != 'n')
				return (flag);
			jdx++;
		}
		flag = 1;
		(*idx)++;
	}
	return (flag);
}

int	echo(char **av)
{
	int	idx;
	int	flag;

	idx = 1;
	flag = 0;
	if (av[idx] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	flag = check_flag(av, &idx);
	while (av[idx])
	{
		ft_putstr_fd(av[idx], 1);
		if (av[idx + 1] != NULL)
			ft_putchar_fd(' ', 1);
		idx++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
