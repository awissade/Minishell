/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell_block.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:41:20 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 10:30:25 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	content_isempty(char *content, int start)
{
	while (content[start] != '(')
	{
		if (ft_isalpha(content[start]))
			return (0);
		start--;
	}
	return (1);
}

int	check_parentheses(char *content)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (content[idx])
	{
		if (content[idx] == '(')
			flag++;
		else if (content[idx] == ')')
		{
			if (content_isempty(content, idx))
				return (syntax_error(UNEXPECTED, ")"));
			flag--;
		}
		idx++;
	}
	if (flag != 0)
	{
		ft_putstr_fd("syntax error: unclosed parentheses\n", 2);
		return (2);
	}
	return (0);
}

int	check_its_subshell_not_arithmetic(char *content)
{
	if (content[1] == '(' && content[ft_strlen(content) - 2] == ')')
		return (1);
	return (0);
}

char	*remove_parentheses(char *str)
{
	int		start;
	int		len;

	start = 0;
	while (ft_isspace(str[start]) || str[start] == '\t')
		start++;
	if (str[start] == '(')
		start++;
	len = ft_strlen(&str[start]) - start + 1;
	if (str[ft_strlen(str) - 1] == ')')
		len--;
	return (substr(str, start, len));
}

int	execute_subshell_block(t_subshellcmd *subshell_block)
{
	int		status;
	pid_t	child_pid;

	if (subshell_block == NULL)
		return (0);
	if (check_its_subshell_not_arithmetic(subshell_block->content) == 1)
		return (1);
	status = check_parentheses(subshell_block->content);
	if (status != 0)
		return (status);
	subshell_block->content = remove_parentheses(subshell_block->content);
	if (subshell_block->content == NULL)
		return (ENOMEM);
	child_pid = fork();
	if (child_pid == -1)
		return (ECHILD);
	if (child_pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		*inparent() = 0;
		end(runcmd(parsing(subshell_block->content)));
	}
	waitpid(child_pid, &status, 0);
	return (((status) & 0xff00) >> 8);
}
