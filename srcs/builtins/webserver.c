/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:30:00 by mariocos          #+#    #+#             */
/*   Updated: 2025/12/31 17:30:00 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void	send_response(int client_fd)
{
	char	*response;
	ssize_t	written;
	ssize_t	total;
	size_t	len;

	response = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 38\r\n"
		"\r\n"
		"<html><body>Webserver 42</body></html>";
	len = ft_strlen(response);
	total = 0;
	while (total < (ssize_t)len)
	{
		written = write(client_fd, response + total, len - total);
		if (written < 0)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		total += written;
	}
}

static void	handle_client(int client_fd)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
	while (bytes_read < 0 && errno == EINTR)
		bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		send_response(client_fd);
	}
	close(client_fd);
}

void	webserver(char **args, int fd)
{
	int					server_fd;
	int					client_fd;
	struct sockaddr_in	address;
	int					opt;
	socklen_t			addrlen;

	(void)args;
	opt = 1;
	addrlen = sizeof(address);
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("minishell: webserver: socket");
		mini_call()->exit_status = 1;
		return ;
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("minishell: webserver: setsockopt");
		close(server_fd);
		mini_call()->exit_status = 1;
		return ;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(4242);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("minishell: webserver: bind");
		close(server_fd);
		mini_call()->exit_status = 1;
		return ;
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("minishell: webserver: listen");
		close(server_fd);
		mini_call()->exit_status = 1;
		return ;
	}
	ft_put_str_fd("Webserver listening on port 4242\n", fd);
	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
		if (client_fd < 0)
		{
			if (errno == EINTR)
				continue ;
			perror("minishell: webserver: accept");
			continue ;
		}
		handle_client(client_fd);
	}
	close(server_fd);
	mini_call()->exit_status = 0;
}
