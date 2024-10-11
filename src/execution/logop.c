/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logop.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:53:16 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 17:13:44 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	logop(t_logopcmd *logop)
{
	int		status;

	if (logop == NULL)
		return (0);
	status = runcmd(logop->left);
	if ((logop->mode == 1 && status != 0) || (logop->mode == 0 && status == 0))
		return (status);
	status = runcmd(logop->right);
	return (status);
}
