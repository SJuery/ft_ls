/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:41:52 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:55:21 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	initialise_flags(t_printf *prtf)
{
	prtf->space = 0;
	prtf->sharp = 0;
	prtf->zero = 0;
	prtf->minus = 0;
	prtf->plus = 0;
	prtf->size = 0;
	prtf->precise = 0;
	prtf->precision = 0;
	prtf->hh = 0;
	prtf->h = 0;
	prtf->ll = 0;
	prtf->l = 0;
	prtf->j = 0;
	prtf->z = 0;
	prtf->c = 0;
}

int			ft_printf(const char *orgstr, ...)
{
	va_list			pargs;
	t_printf		prtf;
	t_fpointer		fptr;

	prtf.ret = 0;
	prtf.len = 0;
	va_start(pargs, orgstr);
	flags_to_converter(&fptr);
	while (orgstr[prtf.len])
	{
		if (orgstr[prtf.len] == '%' && orgstr[prtf.len + 1])
		{
			initialise_flags(&prtf);
			prtf.len += 2 + parse_flags(((char *)orgstr + prtf.len + 1), &prtf);
			prtf.ret += parse_input(pargs, &prtf, &fptr);
		}
		else if (orgstr[prtf.len] != '%' && orgstr[prtf.len])
		{
			ft_putchar(orgstr[prtf.len++]);
			prtf.ret++;
		}
		else
			return (prtf.ret);
	}
	return (prtf.ret);
}
