/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:32 by otodd             #+#    #+#             */
/*   Updated: 2024/01/12 17:50:49 by otodd            ###   ########.fr       */
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
		if (character % 2)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(42);
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
	ft_printf("Target: "BGRN"%d\n"RESET, pid);
	while (*string)
		send_char(*string++, pid);
	return (0);
}
