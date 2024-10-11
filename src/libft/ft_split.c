/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:49:18 by ajawad            #+#    #+#             */
/*   Updated: 2024/05/19 18:16:56 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free(char **array)
{
	int	idx;

	idx = 0;
	while (array[idx])
		free(array[idx++]);
	free(array);
}

static int	wordcounter(const char *str, char c)
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

static char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	fill(const char *str, char **array, char c)
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
		array[index] = malloc(sizeof(char) * (i - tmp + 1));
		if (!array[index])
			return (0);
		ft_strncpy(array[index], &str[tmp], i - tmp);
		index++;
	}
	return (1);
}

char	**ft_split(const char *str, char c)
{
	char	**array;
	int		nbr_words;
	int		checker;

	if (!str)
		return (NULL);
	nbr_words = wordcounter(str, c);
	array = malloc(sizeof(char *) * (nbr_words + 1));
	if (array == NULL)
		return (NULL);
	array[nbr_words] = 0;
	checker = fill(str, array, c);
	if (checker == 0)
	{
		ft_free(array);
		return (NULL);
	}
	return (array);
}
