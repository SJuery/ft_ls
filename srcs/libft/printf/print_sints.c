/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:43:19 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:36:30 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_cortex(long long int arg, t_printf *prtf, int excep)
{
	int		i;

	i = 0;
	if (prtf->plus && arg >= 0)
		ft_putchar('+');
	else if (prtf->space && arg >= 0)
		ft_putchar(' ');
	if (!excep)
		ft_putnbr(arg);
	i += excep ? 0 : ft_intlen(arg);
	return (i + 1);
}

static int	ft_precision(long long int arg, t_printf *prtf, int excep)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (prtf->plus || prtf->space || arg < 0)
		j = 1;
	if (prtf->plus && arg >= 0)
		ft_putchar('+');
	else if (prtf->space && arg >= 0)
		ft_putchar(' ');
	if (arg < 0)
	{
		ft_putchar('-');
		arg = -arg;
	}
	i = excep && arg == 0 ? 0 : ft_intlen(arg);
	while (i < prtf->precision && !excep)
	{
		ft_putchar('0');
		i++;
	}
	if (!excep || (ft_intlen(arg) > prtf->precision && excep && arg != 0))
		ft_putnbr(arg);
	return (i + j);
}

static void	ft_minus_two(long long int arg, t_printf *prtf)
{
	int j;

	j = prtf->precision;
	while (j > ft_intlen(arg))
	{
		ft_putchar('0');
		j--;
	}
}

static int	ft_minus(long long int arg, t_printf *prtf, int excep)
{
	int		i;

	i = 0;
	if (prtf->plus || prtf->space || arg < 0)
		i++;
	if (prtf->plus && arg >= 0)
		ft_putchar('+');
	else if (prtf->space && arg >= 0)
		ft_putchar(' ');
	ft_minus_two(arg, prtf);
	if (!excep)
		ft_putnbr(arg);
	i += prtf->precision > ft_intlen(arg) ? prtf->precision : ft_intlen(arg);
	if (prtf->size)
	{
		while (i < prtf->size)
		{
			ft_putchar(' ');
			i++;
		}
	}
	i -= excep ? ft_intlen(arg) : 0;
	return (i);
}

int			print_sints(long long int arg, t_printf *prtf)
{
	int		i;
	int		excep;

	i = 0;
	excep = (prtf->precise && prtf->precision == 0) ? 1 : 0;
	if (prtf->minus && ((prtf->precision < prtf->size && prtf->precise)
		|| !prtf->precision))
		i += ft_minus(arg, prtf, excep);
	else if (prtf->precise && prtf->precision >= prtf->size)
		i += ft_precision(arg, prtf, excep);
	else if (prtf->size)
		i += size_sints(arg, prtf, excep);
	else if (prtf->plus || prtf->space)
		i += ft_cortex(arg, prtf, excep);
	else
	{
		if (!excep)
			ft_putnbr(arg);
		i = excep ? 0 : ft_intlen(arg);
		i += (arg < 0 ? 1 : 0);
		i += (arg == LLONG_MIN ? 18 : 0);
	}
	return (i);
}
