/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:42:24 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:36:18 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int					parse_deci(va_list pargs, t_printf *prtf)
{
	if (prtf->ll && prtf->spec != 'D')
		prtf->uvals.lli = va_arg(pargs, long long int);
	else if (prtf->l || prtf->spec == 'D')
		prtf->uvals.lli = va_arg(pargs, long int);
	else if (prtf->hh)
		prtf->uvals.lli = (char)va_arg(pargs, int);
	else if (prtf->h)
		prtf->uvals.lli = (short)va_arg(pargs, int);
	else if (prtf->j)
		prtf->uvals.lli = va_arg(pargs, intmax_t);
	else if (prtf->z)
		prtf->uvals.lli = va_arg(pargs, long long int);
	else
		prtf->uvals.lli = va_arg(pargs, int);
	return (print_sints(prtf->uvals.lli, prtf));
}

int					parse_udeci(va_list pargs, t_printf *prtf)
{
	if (prtf->ll && prtf->spec != 'U')
		prtf->uvals.ulli = va_arg(pargs, unsigned long long int);
	else if (prtf->l || prtf->spec == 'U')
		prtf->uvals.ulli = va_arg(pargs, unsigned long int);
	else if (prtf->hh)
		prtf->uvals.ulli = (unsigned char)va_arg(pargs, unsigned int);
	else if (prtf->h)
		prtf->uvals.ulli = (unsigned short)va_arg(pargs, unsigned int);
	else if (prtf->j)
		prtf->uvals.ulli = va_arg(pargs, uintmax_t);
	else if (prtf->z)
		prtf->uvals.lli = va_arg(pargs, size_t);
	else
		prtf->uvals.ulli = va_arg(pargs, unsigned int);
	return (print_ints(ft_itoa_base(prtf->uvals.ulli, 10, 1), prtf, 1));
}

int					parse_hexa(va_list pargs, t_printf *prtf)
{
	if (prtf->ll && prtf->spec != 'p')
		prtf->uvals.ulli = va_arg(pargs, unsigned long long int);
	else if (prtf->l || prtf->spec == 'p')
		if (prtf->spec == 'p')
			prtf->uvals.ulli = (unsigned long int)va_arg(pargs, void *);
		else
			prtf->uvals.ulli = va_arg(pargs, unsigned long int);
	else if (prtf->hh)
		prtf->uvals.ulli = (unsigned char)va_arg(pargs, unsigned int);
	else if (prtf->h)
		prtf->uvals.ulli = (unsigned short)va_arg(pargs, unsigned int);
	else if (prtf->j)
		prtf->uvals.ulli = va_arg(pargs, uintmax_t);
	else if (prtf->z)
		prtf->uvals.lli = va_arg(pargs, size_t);
	else
		prtf->uvals.ulli = va_arg(pargs, unsigned int);
	return (print_ints(conv_hexa(prtf), prtf, 1));
}

int					parse_octa(va_list pargs, t_printf *prtf)
{
	if (prtf->ll && prtf->spec != 'O')
		prtf->uvals.ulli = va_arg(pargs, unsigned long long int);
	else if (prtf->l || prtf->spec == 'O')
		prtf->uvals.ulli = va_arg(pargs, unsigned long int);
	else if (prtf->hh)
		prtf->uvals.ulli = (unsigned char)va_arg(pargs, unsigned int);
	else if (prtf->h)
		prtf->uvals.ulli = (unsigned short)va_arg(pargs, unsigned int);
	else if (prtf->j)
		prtf->uvals.ulli = va_arg(pargs, uintmax_t);
	else if (prtf->z)
		prtf->uvals.lli = va_arg(pargs, size_t);
	else
		prtf->uvals.ulli = va_arg(pargs, unsigned int);
	return (print_ints(conv_octa(prtf), prtf, 0));
}
