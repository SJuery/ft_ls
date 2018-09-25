/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:42:10 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/17 15:15:12 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	flags_to_converter(t_fpointer *fptr)
{
	int i;

	i = 0;
	while (i < 126)
	{
		fptr->converter[i] = &print_per;
		i++;
	}
	fptr->converter['s'] = &parse_str;
	fptr->converter['S'] = &parse_str;
	fptr->converter['p'] = &parse_hexa;
	fptr->converter['d'] = &parse_deci;
	fptr->converter['D'] = &parse_deci;
	fptr->converter['i'] = &parse_deci;
	fptr->converter['o'] = &parse_octa;
	fptr->converter['O'] = &parse_octa;
	fptr->converter['u'] = &parse_udeci;
	fptr->converter['U'] = &parse_udeci;
	fptr->converter['x'] = &parse_hexa;
	fptr->converter['X'] = &parse_hexa;
	fptr->converter['c'] = &parse_char;
	fptr->converter['C'] = &parse_char;
	fptr->converter['%'] = &print_per;
}

int		parse_input(va_list ap, t_printf *prtf, t_fpointer *fptr)
{
	return (fptr->converter[(int)prtf->spec](ap, prtf));
}
