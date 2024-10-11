/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 07:01:47 by ajawad            #+#    #+#             */
/*   Updated: 2024/07/30 15:23:32 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_var_type(char *var)
{
	int	temp1;
	int	temp2;

	temp1 = cm_strstr(var, "+=");
	temp2 = cm_strstr(var, "=");
	if ((temp1 < temp2 && temp1 >= 0) || (temp1 >= 0 && temp2 < 0))
		return ('+');
	else if ((temp2 < temp1 && temp2 >= 0) || (temp2 >= 0 && temp1 < 0))
		return ('=');
	else
		return ('\0');
}

int	compare_variables(char *var1, char *var2)
{
	int		idx;
	char	holder1;
	char	holder2;

	idx = 0;
	holder1 = check_var_type(var1);
	holder2 = check_var_type(var2);
	while (var1[idx] == var2[idx] && var1[idx] != holder1
		&& var2[idx] != holder2 && var1[idx] && var2[idx])
		idx++;
	if (var1[idx] == holder1 && var2[idx] == holder2)
		return (0);
	return (1);
}
