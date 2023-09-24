/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:26:23 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/17 02:04:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./printf.h"
size_t ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

static int calc_number_len(int num)
{
	int i;

	i = ft_calc_num_base_size(num, 10);
	return (i);
}

int print_and_calc_num(int num)
{
	int printed_index;

	printed_index = calc_number_len(num);
	ft_putnbr(num);
	return (printed_index);
}

int print_and_calc_str(char *str)
{
	int printed_index;

	if (!str)
	{
		put_str("(null)");
		return (6);
	}
	printed_index = ft_strlen(str);
	put_str(str);
	return (printed_index);
}

int print_by_format(va_list ap, char c)
{
	int printed_index;

	printed_index = 0;
	if (c == 'c')
	{
		// putchar('a');
		putchar(va_arg(ap, int));
		printed_index++;
	}
	else if (c == 's')
		printed_index += print_and_calc_str(va_arg(ap, char *));
	else if (c == 'p')
		printed_index += print_ptr_adress(va_arg(ap, size_t));
	else if ((c == 'd' || c == 'i'))
		printed_index += print_and_calc_num(va_arg(ap, int));
	else if (c == 'u')
		ft_put_unsigned(va_arg(ap, unsigned int), &printed_index);
	else if ((c == 'x' || c == 'X'))
		printed_index += print_hex(va_arg(ap, int), c);
	else if (c == '%')
	{
		putchar(c);
		printed_index++;
	}
	return (printed_index);
}

int printf(const char *str, ...)
{
	va_list ap;
	int printed_index;
	int i;

	va_start(ap, str);
	printed_index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!str[i + 1])
				break;
			printed_index += print_by_format(ap, str[++i]);
		}
		else
		{
			putchar(str[i]);
			printed_index++;
		}
		i++;
	}
	va_end(ap);
	return (printed_index);
}
