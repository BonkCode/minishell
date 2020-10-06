/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 03:21:08 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/14 15:49:01 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# define ERROR -10
# define MAX_UNSIGNED_INT 4294967295

# include <stdarg.h>

typedef struct	s_directive
{
	int		field_width;
	int		precision;
	char	conversion_character;
	char	*length_modifier;
	char	*flags;
}				t_directive;

int				ft_printf(const char *format_string, ...);
int				get_max(int count, ...);
int				get_min(int count, ...);
long long int	ft_abs(long int n);
long long int	ten_pow(int size);
t_directive		*get_directive(const char **format_string);
char			*get_char_print(t_directive *directive, char variable);
char			*get_int_print(t_directive *directive, long long int variable);
char			*get_pointer_print(t_directive *directive,
								unsigned long int variable);
char			*get_string_print(t_directive *directive, char *variable);
char			*get_unsigned_int_print(t_directive *directive,
								unsigned long long int variable);
char			*f_add_minus_sign(t_directive *directive, double variable,
							char *return_string, char *ptr_to_free);
char			*f_add_plus_or_space(t_directive *directive, double variable,
								char *return_string, char *ptr_to_free);
char			*i_add_minus_sign(t_directive *directive,
								char *str, char *ptr_to_free);
char			*i_add_plus_or_space(t_directive *directive, double variable,
								char *str, char *ptr_to_free);
char			*get_float_print(t_directive *directive, double variable);
char			*get_hex(unsigned long long int variable,
						char conversion_character);
char			*add_hex_rep_ljust(t_directive *directive,
								char *str, char *ptr_to_free);
char			*add_hex_rep_rjust(t_directive *directive,
								char *str, char *ptr_to_free);
char			get_conversion_character(const char **format_string);
int				get_field_width(const char **format_string);
char			*get_flags(const char **format_string);
char			*get_length_modifier(const char **format_string);
int				get_precision(const char **format_string);
char			*choose_int_print_variant(t_directive *directive,
												va_list argptr);
char			*choose_u_int_print_variant(t_directive *directive,
												va_list argptr);
int				spec_case(t_directive *directive, double variable);
void			setup_zeroes(t_directive *directive, char **zeroes,
									char *decimal_part);
void			add_zeroes(char **number_to_print, char *zeroes);
void			add_decimal_part(char **number_to_print, char *decimal_part);

#endif
