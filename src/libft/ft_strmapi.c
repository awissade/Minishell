/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:35:10 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/04 12:11:04 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
 * ft_strmapi - Applies the function ’f’ to each character of the
 *				string ’s’, and passing its index as first argument
 *				to create a new string.
 * @s: The string on which to iterate.
 * @f: The function to apply to each character.
 *
 * Return: The string created from the successive applications of f.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	char			*new_s;
	int				slen;

	if (s == NULL || f == NULL)
		return (NULL);
	idx = 0;
	slen = ft_strlen(s);
	new_s = malloc(sizeof(char) * (slen + 1));
	if (!new_s)
		return (NULL);
	while (s[idx])
	{
		new_s[idx] = f(idx, s[idx]);
		idx++;
	}
	new_s[idx] = '\0';
	return (new_s);
}
