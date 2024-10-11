/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:27:27 by ajawad            #+#    #+#             */
/*   Updated: 2023/11/07 21:18:04 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	numofdigits(int n)
{
	int		num_of_digits;
	long	num;

	num = n;
	num = ft_abs(n);
	num_of_digits = 1;
	while (num > 9)
	{
		num /= 10;
		num_of_digits++;
	}
	return (num_of_digits);
}

static char	*allocate(int num_of_digits)
{
	char	*str;

	str = malloc(sizeof(char) * (num_of_digits + 1));
	if (!str)
		return (NULL);
	return (str);
}

static void	the_25line(char *str_num, int idx, long num)
{
	if (num < 0)
	{
		str_num[0] = '-';
		num *= -1;
	}
	while (num > 9)
	{
		str_num[idx--] = num % 10 + '0';
		num /= 10;
	}
	str_num[idx] = num + '0';
}

char	*ft_itoa(int n)
{
	int		num_of_digits;
	char	*str_num;
	int		idx;
	long	num;

	num = n;
	num_of_digits = numofdigits(n);
	if (num < 0)
		num_of_digits++;
	idx = num_of_digits;
	str_num = allocate(num_of_digits);
	if (!str_num)
		return (NULL);
	str_num[idx--] = '\0';
	the_25line(str_num, idx, num);
	return (str_num);
}
