/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:52:11 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/28 12:13:58 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(int status)
{
	ft_dblfree(*get_env());
	rl_clear_history();
	garbage_collector();
	free(get_localvar()->pwd);
	free(get_localvar()->oldpwd);
	free(get_localvar()->default_path);
	exit(status);
}

void	panic(int status)
{
	ft_dblfree(*get_env());
	rl_clear_history();
	garbage_collector();
	free(get_localvar()->pwd);
	free(get_localvar()->oldpwd);
	free(get_localvar()->default_path);
	exit(status);
}
