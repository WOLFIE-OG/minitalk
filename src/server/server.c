/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/22 13:10:24 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	receive_char(int signum, siginfo_t *info)
{
	static unsigned char	character;
	static int				index;

	character |= (signum == SIGUSR1);
	index++;
	if (index == 8)
	{
		if (character == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(character, 1);
		index = 0;
		character = 0;
	}
	else
		character <<= 1;
}

int	main(void)
{
	struct sigaction	handler;

	handler.sa_handler = &receive_char;
	handler.sa_flags = SA_SIGINFO | SA_RESTART
	ft_printf("Process PID: "BBLU"%d\n"RESET, getpid());
	
	while (1)
		sleep(1);
	return (0);
}
