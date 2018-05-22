/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:41:56 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:35:45 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			parse_char(va_list pargs, t_printf *prtf)
{
	prtf->uvals.c = (char)va_arg(pargs, int);
	return (print_char(prtf->uvals.c, prtf));
}

int			parse_str(va_list pargs, t_printf *prtf)
{
	wchar_t *twchar;

	if (prtf->l || prtf->spec == 'S')
	{
		twchar = va_arg(pargs, wchar_t *);
		if (twchar == NULL)
			prtf->uvals.cp = NULL;
		else if (*twchar == 0)
			return (0);
		else if (twchar)
		{
			if (conv_uni(*twchar))
				prtf->uvals.cp = ft_strdup(conv_uni(*twchar++));
			while (*twchar)
				prtf->uvals.cp = ft_strcat(prtf->uvals.cp, conv_uni(*twchar++));
		}
		return (print_str(prtf));
	}
	else
	{
		prtf->uvals.cp = va_arg(pargs, char *);
		return (print_str(prtf));
	}
	return (0);
}
