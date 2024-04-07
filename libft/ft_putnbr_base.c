/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:56:13 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/06 10:34:48 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbase(long nb, char *base)
{
	write(1, &base[nb % ft_strlen(base)], 1);
}

int	check_base(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	i = 0;
	while (str[i])
	{
		tmp = str[i];
		j = i + 1;
		while (str[j])
		{
			if (tmp == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	size_t	nb;

	i = 0;
	nb = nbr;
	if (ft_strlen(base) >= 2)
	{
		i = check_base(base);
		if (i == 1)
		{
			if (nb < 0)
			{
				write(1, "-", 1);
				nb *= -1;
			}
			if (nb > ft_strlen(base))
				ft_putnbr_base(nb / ft_strlen(base), base);
			ft_putbase(nb, base);
		}
	}
}
