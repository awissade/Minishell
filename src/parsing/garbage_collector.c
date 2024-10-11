/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:11:35 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/25 12:16:51 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**return_head(void)
{
	static t_list	*garbage;

	return (&garbage);
}

void	*safe_alloc(size_t size)
{
	void	*ptr;
	void	*node;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("Fatal");
		panic(ENOMEM);
		return (NULL);
	}
	node = ft_lstnew(ptr);
	if (node == NULL)
	{
		perror("Fatal");
		panic(ENOMEM);
		return (NULL);
	}
	ft_lstadd_back(return_head(), node);
	return (ptr);
}

void	garbage_collector(void)
{
	t_list	*temp;
	t_list	**garbage;

	garbage = return_head();
	while (*garbage)
	{
		temp = (*garbage);
		(*garbage) = (*garbage)->next;
		free(temp->content);
		free(temp);
	}
	*garbage = NULL;
}
