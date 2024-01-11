/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:32 by otodd             #+#    #+#             */
/*   Updated: 2024/01/11 16:10:44 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	send_char(unsigned char c)
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
			ft_printf("1");
		else
			ft_printf("0");
		usleep(42);
	}
	ft_printf(" ");
}

int	main(int arg_n, char **arg_a)
{
	(void)arg_n;
	char	*string;

	string = arg_a[1];
	ft_printf("This is the client.\n");
	while (*string)
		send_char(*string++);
	return (0);
}
