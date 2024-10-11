/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:14:24 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/02 10:04:52 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*_s;
	size_t			i;

	if (s == NULL)
		return ;
	_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		_s[i++] = 0;
	}
}
