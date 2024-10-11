/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:16:37 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/22 16:57:39 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

int	ft_check_newline(char *array)
{
	while (*array)
	{
		if (*array == '\n')
			return (1);
		array++;
	}
	return (0);
}

size_t	newline_idx(char *array)
{
	size_t	len;

	len = 0;
	while (array[len] != '\n' && array[len] != '\0')
		len++;
	if (array[len] == '\n')
		len++;
	return (len);
}

char	*ft_get_remaining(char *read_buff, int flag)
{
	size_t	new_line_len;
	size_t	len;
	int		idx;
	char	*array;

	(void)flag;
	new_line_len = newline_idx(read_buff);
	len = gnl_strlen(read_buff);
	idx = 0;
	if (len - new_line_len == 0)
	{
		return (NULL);
	}
	array = safe_alloc((len - new_line_len) * sizeof(char) + 1);
	if (!array)
		return (NULL);
	while (read_buff[new_line_len])
		array[idx++] = read_buff[new_line_len++];
	array[idx] = '\0';
	return (array);
}

char	*gnl_strjoin(char *buffer, char *array)
{
	char	*new_buffer;
	int		i;
	int		j;

	if (!buffer || !array)
		return (NULL);
	new_buffer = safe_alloc(sizeof(char) * (gnl_strlen(buffer) + \
				newline_idx(array) + 1));
	if (!new_buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	while (array[j] && array[j] != '\n')
		new_buffer[i++] = array[j++];
	if (array[j] == '\n')
		new_buffer[i++] = array[j++];
	new_buffer[i] = '\0';
	return (new_buffer);
}
