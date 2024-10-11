/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:45:08 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 21:19:30 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_core(char *string, char *pattern, t_wildcard *wildcard)
{
	while (wildcard->sidx < wildcard->slen)
	{
		if (wildcard->pidx < wildcard->plen \
				&& (string[wildcard->sidx] == pattern[wildcard->pidx] \
				|| pattern[wildcard->pidx] == '?'))
		{
			++wildcard->sidx;
			++wildcard->pidx;
		}
		else if (wildcard->pidx < wildcard->plen \
				&& pattern[wildcard->pidx] == '*')
		{
			wildcard->wildcard = 1;
			wildcard->sbacktrack_idx = wildcard->sidx;
			wildcard->next_to_wildcard_idx = ++wildcard->pidx;
		}
		else if (wildcard->wildcard == 0)
			return (0);
		else
		{
			wildcard->pidx = wildcard->next_to_wildcard_idx;
			wildcard->sidx = ++wildcard->sbacktrack_idx;
		}
	}
	return (1);
}

int	match(char *string, char *pattern, int slen)
{
	t_wildcard	wildcard;

	if (string[0] == '.' && pattern[0] != '.')
		return (0);
	wildcard.sidx = 0;
	wildcard.pidx = 0;
	wildcard.wildcard = 0;
	wildcard.next_to_wildcard_idx = 0;
	wildcard.sbacktrack_idx = 0;
	wildcard.slen = slen;
	wildcard.plen = ft_strlen(pattern);
	if (match_core(string, pattern, &wildcard) == 0)
		return (0);
	while (pattern[wildcard.pidx])
	{
		if (pattern[wildcard.pidx] != '*')
			return (0);
		wildcard.pidx++;
	}
	return (1);
}

char	*expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*string;

	dir = opendir(".");
	string = cm_strdup("");
	if (dir == NULL)
		return (perror("."), NULL);
	while (1)
	{
		dp = readdir(dir);
		if (dp == NULL)
			break ;
		if (match(dp->d_name, pattern, ft_strlen(dp->d_name)) == 1)
		{
			if (string[0] != '\0')
				string = strjoin(string, " ");
			string = strjoin(string, dp->d_name);
		}
	}
	closedir(dir);
	if (string[0] == '\0')
		return (pattern);
	return (string);
}

char	*get_and_replace(char *arg, int idx, int jdx)
{
	char	*pattern;

	pattern = safe_alloc(sizeof(char) * (jdx - idx + 1 + 1));
	ft_strlcpy(pattern, &arg[idx], jdx - idx + 1 + 1);
	pattern = remove_quotes(pattern);
	return (substr_replace(arg, expand_wildcard(pattern), idx, jdx - idx + 1));
}

char	*catch_wildcards(char *arg)
{
	int		idx;
	int		jdx;
	int		flag;
	char	*newarg;

	idx = -1;
	newarg = cm_strdup(arg);
	while (arg[++idx])
	{
		if (idx == 0 || ft_isspace(arg[idx - 1]))
		{
			flag = 0;
			jdx = idx;
			while (!ft_strchr("|&>< \t", arg[jdx]) && arg[jdx])
			{
				if (arg[jdx] == '*' || arg[jdx] == '?')
					flag = 1;
				jdx++;
			}
			if (flag == 1)
				newarg = get_and_replace(arg, idx, --jdx);
		}
	}
	return (newarg);
}
