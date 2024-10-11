/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <ajawad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:44:29 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 18:38:17 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredocs(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->prev != NULL && tokens->prev->type == 'h')
		{
			tokens->content = get_heredoc_input(tokens->content);
			if (tokens->content == NULL)
				return (12);
		}
		tokens = tokens->next;
	}
	return (0);
}

t_cmd	*parsing(char *line)
{
	int					status;
	t_cmd				*cmd;
	t_token				*tokens;

	cmd = NULL;
	tokens = tokenizer(catch_wildcards(line));
	if (tokens == NULL)
		return (NULL);
	if (tokens->content[0] == '\0')
		return (get_localvar()->exit_status = 0, NULL);
	status = validator(tokens);
	if (status != 0)
	{
		get_localvar()->exit_status = status;
		return (NULL);
	}
	check_numof_heredocs(tokens);
	if (handle_heredocs(tokens) == 12)
		return (NULL);
	cmd = parse_cmd(tokens);
	return (cmd);
}

void	minishell(void)
{
	t_cmd	*cmd;
	char	*input;
	char	*holder;

	while (1)
	{
		*inparent() = 1;
		*isreturning() = 0;
		input = readline("minishell$ ");
		if (input == NULL)
			exit(get_localvar()->exit_status);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		holder = cm_strdup(input);
		free(input);
		cmd = parsing(holder);
		if (cmd != NULL)
			get_localvar()->exit_status = runcmd(cmd);
		garbage_collector();
	}
}
