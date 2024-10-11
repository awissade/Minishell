/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:49:18 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/31 19:53:33 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcounter(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i
					+ 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	fill(char *str, char **array, char c)
{
	int	i;
	int	tmp;
	int	index;

	i = 0;
	index = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		tmp = i;
		while (str[i] != c && str[i])
			i++;
		array[index] = safe_alloc(sizeof(char) * (i - tmp + 1));
		if (!array[index])
			return (0);
		ft_strncpy(array[index], &str[tmp], i - tmp);
		index++;
	}
	return (1);
}

char	**split(char *str, char c)
{
	char	**array;
	int		nbr_words;
	int		checker;

	if (!str)
		return (NULL);
	nbr_words = wordcounter(str, c);
	array = safe_alloc(sizeof(char *) * (nbr_words + 1));
	if (array == NULL)
		return (NULL);
	array[nbr_words] = 0;
	checker = fill(str, array, c);
	if (checker == 0)
		return (NULL);
	return (array);
}
