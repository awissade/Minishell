/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:56:37 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/25 11:57:41 by awissade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_replace(char *str, char *substr, int start, int place_len)
{
	char	*newstr;
	int		len;

	len = ft_strlen(str) - place_len + ft_strlen(substr) + 1;
	newstr = safe_alloc(sizeof(char) * len);
	ft_strncpy(newstr, str, start);
	ft_strlcat(newstr, substr, len);
	ft_strlcat(newstr, &str[start + place_len], len);
	return (newstr);
}
