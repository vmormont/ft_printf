/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:21:14 by vmormont          #+#    #+#             */
/*   Updated: 2019/10/20 20:21:15 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	minus_pos(char *i, t_param list, int tmp, t_buf *buf)
{
	if (list.precision > tmp)
		ft_buf_add_s(buf, ft_memnew(list.precision - tmp, '0'), 0);
	ft_buf_add_s(buf, i, 0);
	if (list.width > list.precision && list.width > tmp && list.zero == 1)
		ft_buf_add_s(buf, ft_memnew(list.width - list.space -
				(list.precision > tmp ? list.precision : tmp), '0'), 0);
	if (list.width > list.precision && list.width > tmp)
		ft_buf_add_s(buf, ft_memnew(list.width - list.space -
			(list.precision > tmp ? list.precision : tmp), ' '), 0);
}

static void	prec_neg(char *i, t_param list, int tmp, t_buf *buf)
{
	if (list.minus == 0 && list.zero == 0 && list.width > tmp)
		ft_buf_add_s(buf, ft_memnew(list.width - tmp, ' '), 0);
	if (list.minus == 0 && list.zero == 1 && list.width > tmp)
		ft_buf_add_s(buf, ft_memnew(list.width - tmp, '0'), 0);
	ft_buf_add_s(buf, i, 0);
	if (list.minus == 1 && list.width > tmp)
		ft_buf_add_s(buf, ft_memnew(list.width - tmp, ' '), 0);
}

static void	prec_pos(char *i, t_param list, int tmp, t_buf *buf)
{
	*i == '0' && list.precision == 0 ? tmp -= 1 : 0;
	if (list.width > list.precision && list.width > tmp)
		ft_buf_add_s(buf, ft_memnew(list.width - list.space -
			(list.precision > tmp ? list.precision : tmp), ' '), 0);
	if (list.width > list.precision && list.width > tmp && list.zero == 1)
		ft_buf_add_s(buf, ft_memnew(list.width - list.space -
			(list.precision > tmp ? list.precision : tmp), '0'), 0);
	if (list.precision > tmp)
		ft_buf_add_s(buf, ft_memnew(list.precision - tmp, '0'), 0);
	*i == '0' && list.precision == 0 ? NULL : ft_buf_add_s(buf, i, 0);
}

static void	ft_type_u(t_param list, char *i, t_buf *buf)
{
	list.precision > -1 ? list.zero = 0 : 0;
	if (list.precision == -1)
		prec_neg(i, list, ft_strlen(i), buf);
	else if (list.minus == 0)
		prec_pos(i, list, ft_strlen(i), buf);
	else if (list.minus == 1)
		minus_pos(i, list, ft_strlen(i), buf);
}

void		ft_u(t_param list, va_list ap, t_buf *buf)
{
	if (list.length == 0)
		ft_type_u(list,
		ft_itoa_base_ll((unsigned)va_arg(ap, unsigned), 10), buf);
	else if (list.length == 'l')
		ft_type_u(list,
		ft_itoa_base_ll((unsigned long)va_arg(ap, unsigned long), 10), buf);
	else if (list.length == 'l' + 'l')
		ft_type_u(list,
		ft_itoa_base_ll((unsigned long long)va_arg(ap, unsigned long long),
		10), buf);
	else if (list.length == 'h')
		ft_type_u(list,
			ft_itoa_base_ll((unsigned short)va_arg(ap, unsigned), 10), buf);
	else if (list.length == 'h' + 'h')
		ft_type_u(list,
				ft_itoa_base_ll((unsigned char)va_arg(ap, unsigned), 10), buf);
	else if (list.length == 'j')
		ft_type_u(list,
				ft_itoa_base_ll((uintmax_t)va_arg(ap, uintmax_t), 10), buf);
	else if (list.length == 'z')
		ft_type_u(list, ft_itoa_base_ll((size_t)va_arg(ap, size_t), 10), buf);
}
