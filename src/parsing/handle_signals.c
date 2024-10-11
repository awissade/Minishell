/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:58:54 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 18:38:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_termsig(void)
{
	static int	child_term_sig;

	return (&child_term_sig);
}

int	*get_heredoc_termsig(void)
{
	static int	heredoc_term_sig;

	return (&heredoc_term_sig);
}

void	handle_signals(int signum)
{
	if (signum == SIGINT && *get_termsig() == 1)
	{
	}
	else if (signum == SIGINT && *get_heredoc_termsig() == 1)
	{
		ft_putchar_fd('\n', 1);
		end(130);
	}
	else if (signum == SIGINT && *get_heredoc_termsig() == 0 \
			&& *get_termsig() == 0 && *isreturning() == 0)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_localvar()->exit_status = 130;
	}
}
