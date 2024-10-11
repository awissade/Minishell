/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:02:00 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/28 17:00:06 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_localvar(t_localvar *localvar)
{
	char	*holder;

	holder = "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.";
	localvar->pwd = ft_strdup(ft_getenv("PWD"));
	localvar->oldpwd = ft_strdup(ft_getenv("OLDPWD"));
	localvar->default_path = ft_strdup(holder);
	if (ft_getenv("PATH") == NULL)
		localvar->path_unset = 0;
	else if (ft_getenv("PATH") != NULL)
		localvar->path_unset = -1;
}

void	ft_dblfree(char **ptr)
{
	int	idx;

	idx = 0;
	while (ptr[idx])
	{
		free(ptr[idx]);
		idx++;
	}
	free(ptr);
}

void	skip_spaces(char **str)
{
	while (ft_isspace(*(*str)))
		(*str)++;
}

t_token	*peek(t_token *tokens_head, char type)
{
	while (tokens_head != NULL)
	{
		if (tokens_head->type == type)
			return (tokens_head);
		tokens_head = tokens_head->next;
	}
	return (NULL);
}

char	**get_command_args(t_token *tokens_head)
{
	char	**cmdargs;
	t_token	*temp;
	int		len;
	int		idx;

	len = 0;
	idx = 0;
	temp = tokens_head;
	while (temp != NULL)
	{
		if (temp->type == 'a')
			len++;
		temp = temp->next;
	}
	cmdargs = safe_alloc(sizeof(char *) * (len + 1));
	cmdargs[len] = NULL;
	while (tokens_head != NULL)
	{
		if (tokens_head->type == 'a')
			cmdargs[idx++] = tokens_head->content;
		tokens_head = tokens_head->next;
	}
	return (cmdargs);
}
