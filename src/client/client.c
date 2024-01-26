/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:32 by otodd             #+#    #+#             */
/*   Updated: 2024/01/26 13:53:02 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

t_signal_count	*g_signal_count;

static void	receive_pong(int sigint)
{
	static size_t	count;

	if (sigint == SIGUSR1)
		count++;
	else if (sigint == SIGUSR2)
		count++;
	if (count == g_signal_count->len)
		g_signal_count->is_complete = true;

}

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
		{
			kill(pid, SIGUSR2);
			g_signal_count->len++;
		}
		else
		{
			kill(pid, SIGUSR1);
			g_signal_count->len++;
		}
		usleep(WAIT_TIME);
	}
}

static void	result(void)
{
	if (g_signal_count->is_complete == true)
		ft_printf(BGRN"Server sent the correct amount of chars!\n"RESET);
	else
		ft_printf(BRED"Server didn't send the correct amount of chars!\n"RESET);
	free(g_signal_count);
}

void	create_sig_counter(void)
{
	g_signal_count = malloc(sizeof(t_signal_count));
	if (!g_signal_count)
		exit(EXIT_FAILURE);
}

int	main(int arg_n, char **arg_a)
{
	char	*string;
	pid_t	pid;

	if (arg_n < 3)
	{
		ft_printf(BRED"Not enough args to execute!"RESET);
		exit(EXIT_FAILURE);
	}
	if (ft_ischeck_str(arg_a[1], ft_isdigit))
	{
		ft_printf(BRED"Invalid PID!"RESET);
		exit(EXIT_FAILURE);
	}
	create_sig_counter();
	signal(SIGUSR1, receive_pong);
	signal(SIGUSR2, receive_pong);
	string = arg_a[2];
	pid = ft_atoi(arg_a[1]);
	while (*string)
		send_char(*string++, pid);
	send_char('\0', pid);
	result();
	return (0);
}
