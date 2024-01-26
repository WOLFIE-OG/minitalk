/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:08 by otodd             #+#    #+#             */
/*   Updated: 2024/01/26 14:01:08 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# ifndef WAIT_TIME
#  define WAIT_TIME 100
# endif
# include "../libft/include/libft.h"
# include "colour_codes.h"
# include <signal.h>
# include <stdbool.h>

typedef struct s_signal_count
{
	bool	is_complete;
	size_t	i_len;
	size_t	o_len;
}	t_signal_count;

#endif