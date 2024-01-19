/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolfie <wolfie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:16 by otodd             #+#    #+#             */
/*   Updated: 2024/01/16 17:16:15 by wolfie           ###   ########.fr       */
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
		if (character == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", character);
		index = 0;
		character = 0;
	}
	else
		character <<= 1;
}

int	main(void)
{
	ft_printf("Process PID: "BBLU"%d\n"RESET, getpid());
	signal(SIGUSR1, convert_char);
	signal(SIGUSR2, convert_char);
	while (1)
		pause();
	return (0);
}
