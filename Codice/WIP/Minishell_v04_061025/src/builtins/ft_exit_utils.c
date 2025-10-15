/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:13:58 by aielo             #+#    #+#             */
/*   Updated: 2025/10/14 12:22:31 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static const char	*skip_spaces_and_sign(const char *str, int *sign);
static int			check_overflow(long long result, int digit, int sign);

int	ft_is_numeric(const char *str)
{
	int	sign;

	sign = 1;
	str = skip_spaces_and_sign(str, &sign);
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atol_limit_check(const char *str, long long *val_out)
{
	long long	result;
	int			sign;
	int			digit;

	if (!str || !val_out)
		return (1);
	result = 0;
	sign = 1;
	str = skip_spaces_and_sign(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_overflow(result, digit, sign))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	*val_out = result * sign;
	return (0);
}

static const char *skip_spaces_and_sign(const char *str, int *sign)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static int check_overflow(long long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& digit > LLONG_MAX % 10))
			return (1);
	}
	else
	{
		if (result > -(LLONG_MIN / 10) || (result == -(LLONG_MIN / 10)
				&& digit > -(LLONG_MIN % 10)))
			return (1);
	}
	return (0);
}

/*
static int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

exit hello	bash: exit: hello: numeric argument required	255
exit 1 2	bash: exit: too many arguments	1 (The shell does not exit)

int	exit_status()
{
	printf("%d\n", WEXITSTATUS(status));
	
	exit(last_command_status);


static int	ft_exit_status(t_minishell *shell, char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
		{
		if (args[1][i] < '0' || args[1][i] > '9')
			{
				print_unquoted_error("exit", args[1],
					"numeric argument required");
				shell->last_exit_status = 255;
				return (1);
			}
			i++;
		}
	shell->last_exit_status = (atoi(args[1]) % 256);
	return (0);
}
}
https://linuxize.com/post/bash-exit/
*/