/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalshbou <oalshbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:52:44 by oalshbou          #+#    #+#             */
/*   Updated: 2026/02/02 17:52:48 by oalshbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

void	handle_signals(int sig)
{
	static int	bit_count = 0;
	static int	current_char = 0;
	static char	*message = NULL;

	if (sig == SIGUSR2)
		current_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
		{
			if (message)
			{
				write(1, message, ft_strlen(message));
				write(1, "\n", 1);
				free(message);
				message = NULL;
			}
		}
		else
			message = ft_append_char(message, current_char);
		bit_count = 0;
		current_char = 0;
	}
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
