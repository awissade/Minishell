/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:30:46 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/09 11:03:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*inparent(void)
{
	static int	flag;

	return (&flag);
}

int	is_digit(char *arg)
{
	int	len;
	int	idx;

	idx = 0;
	len = ft_strlen(arg);
	if (arg[idx] == '-' || arg[idx] == '+')
	{
		idx++;
		len--;
	}
	while (arg[idx])
	{
		if (ft_isdigit(arg[idx]) == 1)
			len--;
		idx++;
	}
	return (len);
}

int	builtin_exit(char	**av)
{
	if (*inparent() == 1)
		ft_putstr_fd("exit\n", 2);
	if (av[1] == NULL)
		end(get_localvar()->exit_status);
	else if (is_digit(av[1]) == 0 && av[2] == NULL)
		get_localvar()->exit_status = (unsigned char)ft_atoi(av[1]);
	else if (is_digit(av[1]) == 0 && av[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (is_digit(av[1]) != 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		get_localvar()->exit_status = 2;
	}
	end(get_localvar()->exit_status);
	return (0);
}
