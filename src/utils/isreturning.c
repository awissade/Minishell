/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isreturning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:36:35 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/08 18:36:52 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*isreturning(void)
{
	static int	returning;

	return (&returning);
}
