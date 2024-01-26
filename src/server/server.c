/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/26 14:15:04 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	send_pong(int signum, siginfo_t *info)
{
	if (signum == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signum == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

static void	receive_char(int signum, siginfo_t *info, void *ctx)
{
	static unsigned char	character;
	static int				index;

	(void)ctx;
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
	send_pong(signum, info);
}

int	main(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = &receive_char;
	handler.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&handler.sa_mask);
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	ft_printf("Process PID: "BBLU"%d\n"RESET, getpid());
	while (1)
		sleep(1);
	return (0);
}
