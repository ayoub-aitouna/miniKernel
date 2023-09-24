/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:26:23 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/17 02:04:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef printf_H
#define printf_H

#include "../../driver/screen.h"
#include <stdarg.h>

typedef unsigned int size_t;

int printf(const char *str, ...);
int ft_calc_num_base_size(long int n, int base);
void ft_converter_base_hex(unsigned long int n, char format, int *size);
void ft_put_unsigned(unsigned int num, int *i);
int print_hex(unsigned int n, char formate);
int print_ptr_adress(size_t n);

#endif
