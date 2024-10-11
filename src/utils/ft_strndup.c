/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:31:04 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/25 12:23:55 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*new_str;

	new_str = safe_alloc(sizeof(char) * n + 1);
	new_str = ft_strncpy(new_str, str, n);
	new_str[n] = '\0';
	return (new_str);
}
