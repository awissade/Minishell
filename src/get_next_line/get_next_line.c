/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:02:30 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/24 14:42:36 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return(char *buffer, char *read_buff, char **array)
{
	(void)read_buff;
	if (gnl_strlen(buffer))
		return (buffer);
	else if (*array != NULL)
		return (*array = NULL, NULL);
	else
		return (NULL);
}

char	*ft_get_line(int fd, char *buffer, char **array, char *read_buff)
{
	ssize_t	read_byte;

	if (*array != NULL && gnl_strlen(*array) > 0)
	{
		buffer = gnl_strjoin(buffer, *array);
		if (ft_check_newline(buffer))
		{
			*array = ft_get_remaining(*array, 1);
			return (buffer);
		}
		*array = NULL;
	}
	while (1)
	{
		read_byte = read(fd, read_buff, BUFFER_SIZE);
		if (read_byte <= 0)
			return (ft_return(buffer, read_buff, array));
		read_buff[read_byte] = '\0';
		buffer = gnl_strjoin(buffer, read_buff);
		if (ft_check_newline(read_buff) == 1)
			return (*array = ft_get_remaining(read_buff, 0), buffer);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*array;
	char		*buffer;
	char		*read_buff;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = safe_alloc((size_t)BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	read_buff = safe_alloc((size_t)BUFFER_SIZE + 1 * sizeof(char));
	if (!read_buff)
		return (NULL);
	buffer = ft_get_line(fd, buffer, &array, read_buff);
	return (buffer);
}
