/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:51:41 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/26 09:38:53 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(void)
{
	int		idx;
	char	**env_var;

	env_var = *get_env();
	idx = 0;
	while (env_var[idx])
	{
		if (ft_strchr(env_var[idx], '='))
		{
			ft_putstr_fd(env_var[idx], 1);
			ft_putchar_fd('\n', 1);
		}
		idx++;
	}
	return (0);
}
