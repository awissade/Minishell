/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_additional.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:58:47 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/09 11:21:19 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error(void)
{
	ft_putstr_fd("maximum here-document count exceeded\n", 2);
	panic(2);
}

int	check_following(t_token *tokens)
{
	if (tokens->next && tokens->next->type == '(')
		return (syntax_error(UNEXPECTED, "("));
	return (0);
}

void	check_numof_heredocs(t_token *tokens)
{
	char	*holder;
	int		size;
	int		sum;

	sum = 0;
	while (tokens)
	{
		if (tokens->type == 'h')
			sum++;
		else if (tokens->type == '(')
		{
			size = ft_strlen(tokens->content) + 1;
			holder = ft_strnstr(tokens->content, "<<", size);
			while (holder != NULL)
			{
				sum++;
				while (*holder == '<')
					holder++;
				holder = ft_strnstr(holder, "<<", size);
			}
		}
		tokens = tokens->next;
	}
	if (sum > 16)
		error();
}
