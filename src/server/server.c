/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/22 12:24:38 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	receive_char(int signum)
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
	ft_printf("Process PID: "BBLU"%d\n"RESET, getpid());
	signal(SIGUSR1, receive_char);
	signal(SIGUSR2, receive_char);
	while (1)
		sleep(1);
	return (0);
}
