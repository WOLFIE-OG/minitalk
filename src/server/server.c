/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/12 17:20:02 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static void	convert_char(int signum)
{
	static unsigned char	character;
	static int				index;

	character |= (signum == SIGUSR1);
	index++;
	if (index == 8)
	{
		ft_printf("%c", character);
		index = 0;
		character = 0;
	}
	else
		character <<= 1;
}

int	main(void)
{
	signal(SIGUSR1, convert_char);
	signal(SIGUSR2, convert_char);
	ft_printf("Process PID: "BBLU"%d\n"RESET, getpid());
	while (1)
		usleep(42);
	return (0);
}
