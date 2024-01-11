/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:32 by otodd             #+#    #+#             */
/*   Updated: 2024/01/11 16:29:38 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	send_char(unsigned char c, int pid)
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
	(void)arg_n;
	char	*string;
	int		pid;

	string = arg_a[2];
	pid = ft_atoi(arg_a[1]);
	ft_printf("This is the client. Target: %d\n", pid);
	while (*string)
		send_char(*string++, pid);
	return (0);
}
