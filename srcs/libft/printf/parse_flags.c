/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:42:27 by sjuery            #+#    #+#             */
/*   Updated: 2018/01/30 20:36:13 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		parse_shpm(char c, t_printf *prtf)
{
	if (c == '-')
		prtf->minus = 1;
	else if (c == '+')
		prtf->plus = 1;
	else if (c == '#')
		prtf->sharp = 1;
	else if (c == ' ')
		prtf->space = 1;
}

static int		parse_width(char *s, t_printf *prtf)
{
	int i;

	i = 0;
	if (s[i] == '0')
	{
		prtf->zero = 1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		prtf->size = prtf->size * 10 + (s[i] - '0');
		i++;
	}
	return (i - 1);
}

static int		parse_size(char *s, t_printf *prtf)
{
	int i;

	i = 0;
	if (s[i] == 'h' && s[i + 1] != 'h')
		prtf->h = 1;
	else if (s[i] == 'h' && s[i + 1] == 'h')
	{
		prtf->hh = 1;
		i++;
	}
	else if (s[i] == 'l' && s[i + 1] != 'l')
		prtf->l = 1;
	else if (s[i] == 'l' && s[i + 1] == 'l')
	{
		prtf->ll = 1;
		i++;
	}
	else if (s[i] == 'j')
		prtf->j = 1;
	else if (s[i] == 'z')
		prtf->z = 1;
	return (i);
}

static int		parse_precision(char *s, t_printf *prtf)
{
	int i;

	i = 0;
	prtf->precise = 1;
	while (s[i] == '.')
		i++;
	while (s[i])
	{
		while (ft_isdigit(s[i]) && s[i])
		{
			prtf->precision = prtf->precision * 10 + (s[i] - '0');
			i++;
		}
		return (i - 1);
	}
	return (i--);
}

int				parse_flags(char *orgstr, t_printf *prtf)
{
	int		i;

	i = 0;
	while (orgstr[i])
	{
		if (orgstr[i] == '#' || orgstr[i] == '+' || orgstr[i] == '-'
			|| orgstr[i] == ' ')
			parse_shpm(orgstr[i], prtf);
		else if (ft_isdigit(orgstr[i]))
			i += parse_width(&orgstr[i], prtf);
		else if (orgstr[i] == 'h' || orgstr[i] == 'l' || orgstr[i] == 'j'
			|| orgstr[i] == 'z')
			i += parse_size(&orgstr[i], prtf);
		else if (orgstr[i] == '.')
			i += parse_precision(&orgstr[i], prtf);
		else
		{
			prtf->spec = orgstr[i];
			return (i);
		}
		i++;
	}
	return (i);
}
