/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/11 17:13:58 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	handler(int signum)
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
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_printf("This is the server. %d", getpid());
	while (1)
		usleep(42);
	return (0);
}
