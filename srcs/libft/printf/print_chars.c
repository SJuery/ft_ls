/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:43:16 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 15:10:42 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	null_precision(t_printf *prtf)
{
	int		len;

	len = 0;
	while (len < prtf->precision)
	{
		if (len <= prtf->precision)
		{
			write(1, &prtf->uvals.cp[len], ft_widelen(prtf->uvals.cp[len]));
			len += ft_widelen(prtf->uvals.cp[len]);
		}
	}
	return (len);
}

static int	no_minus(t_printf *prtf, char *c, int j)
{
	int i;

	i = 0;
	if (prtf->size)
		j = prtf->precise ? (prtf->size - prtf->precision) : (prtf->size - j);
	else
		j = 0;
	if (prtf->size)
		while (i < j)
		{
			write(1, c, ft_strlen(c));
			i += ft_strlen(c);
		}
	free(c);
	if (prtf->precision < (int)ft_strlen(prtf->uvals.cp))
		i += null_precision(prtf);
	if (!prtf->precise)
	{
		write(1, prtf->uvals.cp, (int)ft_strlen(prtf->uvals.cp));
		i += (int)ft_strlen(prtf->uvals.cp);
	}
	return (i);
}

static int	flag_args(t_printf *p)
{
	char	*c;
	int		i;

	i = 0;
	c = p->zero ? conv_uni('0') : conv_uni(' ');
	if (p->precise)
		p->precise = (p->precision < (int)(ft_strlen(p->uvals.cp))) ? 1 : 0;
	if (p->minus)
	{
		if (p->precise)
			i += null_precision(p);
		else
		{
			i = ft_strlen(p->uvals.cp);
			write(1, p->uvals.cp, i);
		}
		while (i < p->size)
		{
			write(1, c, ft_strlen(c));
			i += ft_strlen(c);
			free(c);
		}
		return (i);
	}
	return (i + no_minus(p, c, ft_strlen(p->uvals.cp)));
}

int			print_char(char arg, t_printf *prtf)
{
	int i;

	i = 0;
	if (prtf->size && !prtf->zero && !prtf->minus)
		i = zero_minus_space(prtf->size, arg, ' ');
	else if (prtf->size && prtf->zero && !prtf->minus)
		i = zero_minus_space(prtf->size, arg, '0');
	else if (prtf->size && prtf->minus)
		i = zero_minus_space(prtf->size, arg, '-');
	else
	{
		i = 1;
		ft_putchar(arg);
	}
	return (i);
}

int			print_str(t_printf *prtf)
{
	if (!prtf->uvals.cp)
		prtf->uvals.cp = ft_strdup("(null)");
	if (prtf->size || prtf->precise || prtf->uvals.cp || !prtf->uvals.cp)
		return (flag_args(prtf));
	else
	{
		write(1, prtf->uvals.cp, ft_strlen(prtf->uvals.cp));
		return (ft_strlen(prtf->uvals.cp));
	}
	return (0);
}
