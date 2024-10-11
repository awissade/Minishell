/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:29:41 by ajawad            #+#    #+#             */
/*   Updated: 2024/06/26 21:30:11 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	idx;

	idx = 0;
	while (src[idx] && n > 0)
	{
		dest[idx] = src[idx];
		idx++;
		n--;
	}
	dest[idx] = '\0';
	return (dest);
}
