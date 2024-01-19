/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:32 by otodd             #+#    #+#             */
/*   Updated: 2024/01/19 13:11:29 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	send_char(unsigned char c, int pid)
{
	int				bit;
	unsigned char	character;

	bit = 8;
	character = c;
	while (bit > 0)
	{
		bit--;
		character = c >> bit;
		if (character % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int arg_n, char **arg_a)
{
	char	*string;
	int		pid;

	if (arg_n < 3)
	{
		ft_printf(BRED"Not enough args to execute!"RESET);
		exit(EXIT_FAILURE);
	}
	if (ft_isdigit_str(arg_a[1]))
	{
		ft_printf(BRED"Invalid PID!"RESET);
		exit(EXIT_FAILURE);
	}
	string = arg_a[2];
	pid = ft_atoi(arg_a[1]);
	while (*string)
		send_char(*string++, pid);
	send_char('\0', pid);
	return (0);
}
