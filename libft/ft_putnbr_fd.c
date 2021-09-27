/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:02:18 by eassouli          #+#    #+#             */
/*   Updated: 2019/10/21 11:58:52 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nb;
	long	ln;

	ln = (long)n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = -ln;
	}
	if (ln > 9)
		ft_putnbr_fd(ln / 10, fd);
	nb = ln % 10 + '0';
	write(fd, &nb, 1);
}
