/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:42:00 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:35:36 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			zero_minus_space(int size, char c, char zms)
{
	int i;

	i = 0;
	if (zms == '-')
		ft_putchar(c);
	while (i < (size - 1))
	{
		if (zms == '0')
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
	}
	if (zms == ' ' || zms == '0')
		ft_putchar(c);
	return (i + 1);
}

static int	precision(t_printf *prtf, int i, int j, long long int arg)
{
	prtf->arg = arg;
	while (i < prtf->size + j)
	{
		ft_putchar(prtf->c);
		i++;
	}
	i -= j;
	if (prtf->plus && arg > 0 && prtf->c == ' ')
		ft_putchar('+');
	if (prtf->precision && arg < 0)
	{
		ft_putchar('-');
		prtf->arg = -arg;
	}
	while (prtf->precision > ft_intlen(arg))
	{
		ft_putchar('0');
		prtf->precision--;
	}
	return (i);
}

int			size_sints(long long int arg, t_printf *prtf, int excep)
{
	int		i;
	int		j;

	i = 0;
	if (prtf->plus || prtf->space || arg < 0)
		i++;
	if (!prtf->precise)
		prtf->c = prtf->zero == 1 ? '0' : ' ';
	else
		prtf->c = ' ';
	if (prtf->plus && arg >= 0 && prtf->c == '0')
		ft_putchar('+');
	else if (prtf->space && arg >= 0 && !prtf->plus)
		ft_putchar(' ');
	if ((arg < 0 && prtf->c == '0'))
	{
		ft_putchar('-');
		arg = -arg;
	}
	i += prtf->precision > ft_intlen(arg) ? prtf->precision : ft_intlen(arg);
	j = excep && arg == 0 ? 1 : 0;
	i = precision(prtf, i, j, arg);
	if (!excep)
		ft_putnbr(prtf->arg);
	return (i);
}
