/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:30:45 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 15:55:34 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intcount(unsigned int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				count;
	char			*nb;

	num = n;
	if (n < 0)
		num = -n;
	count = ft_intcount(num);
	if (n <= 0)
		count++;
	nb = malloc(sizeof(char) * (count + 1));
	if (nb == NULL)
		return (NULL);
	nb[count] = '\0';
	while (count-- != 0)
	{
		nb[count] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		nb[0] = '-';
	return (nb);
}
