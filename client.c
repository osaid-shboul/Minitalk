/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalshbou <oalshbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:52:52 by oalshbou          #+#    #+#             */
/*   Updated: 2026/02/02 17:53:30 by oalshbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	send_bits(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1000);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			send_bits(pid, argv[2][i]);
			i++;
		}
		send_bits(pid, '\0');
	}
	else
	{
		write(1, "Error: Use ./client [PID] [STR]\n", 32);
	}
	return (0);
}
