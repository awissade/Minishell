/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_functions_additional.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:08:19 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/22 19:08:37 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*subshell_block(char *content)
{
	t_subshellcmd	*subshell_block;

	subshell_block = safe_alloc(sizeof(t_subshellcmd));
	subshell_block->type = SUBSHELL;
	subshell_block->content = content;
	return ((t_cmd *)subshell_block);
}
