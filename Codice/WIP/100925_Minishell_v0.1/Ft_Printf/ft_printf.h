/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:03:55 by aielo             #+#    #+#             */
/*   Updated: 2025/06/27 23:41:43 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_flags
{
	int	left;
	int	zero;
	int	plus;
	int	space;
	int	sharp;
	int	width;
	int	prec;
}	t_flags;

int		ft_printf(const char *format, ...);
int		ft_is_specifier(char c);
int		ft_parse_and_print(const char *format, va_list *arg_list);
int		ft_format_identifier(char fi, va_list *arg_list, t_flags *flag);
int		ft_format_identifier_c(va_list *arg_list, t_flags *flag);
int		ft_format_identifier_s(va_list *arg_list, t_flags *flag);
int		ft_format_identifier_di(va_list *arg_list, t_flags *flag);
int		ft_format_identifier_u(va_list *arg_list, t_flags *flag);
int		ft_format_identifier_x(char fi, va_list *arg_list, t_flags *flag);
int		ft_format_identifier_p(va_list *arg_list, t_flags *flag);
int		ft_format_identifier_per(t_flags *flag);
void	ft_set_flags(t_flags *flag);
int		ft_find_size(const char *format, int i, int *size);
int		ft_check_flags(const char *format, t_flags *flag, int i);
int		ft_check_flags_a(const char *format, t_flags *flag, int i);
int		ft_check_flags_b(const char *format, t_flags *flag, int i);
int		ft_flag_width(t_flags *flag, int printed);
int		ft_flag_pre_s(int *size, int printed, char **str);
int		ft_flag_pre_di(int *size, int length, int value);
int		ft_flag_pre_x(int *size, int length);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_itoa_u(unsigned int n);
char	*ft_itoa_x(unsigned int n, int upper);
char	*ft_itoa_p(uintptr_t n, int upper);

#endif
