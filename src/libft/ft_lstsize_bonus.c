/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:34:03 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 13:22:12 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * ft_lstsize - Counts the number of nodes in a list.
 * @lst: The beginning of the list.
 *
 * Return: The length of the list.
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		size;

	size = 0;
	node = lst;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}
