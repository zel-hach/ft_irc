/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:39:50 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/09 21:26:32 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(Server &s)
{
	*this = s;
}

Server::Server()
{
}

Server &Server::operator=(Server &s)
{
	if (this != &s)
	{
		this->serversocket = s.serversocket;
		this->client = s.client;
	}
	return (*this);
}

Server::~Server()
{
}
int Server::create_socket()
{
	int opt = 1;
	int serversocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serversocket == -1)
	{
		perror("Error in socket creation.\n");
		return 1;
	}
	if (setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
				   sizeof(opt)) < 0)
	{
		perror("Error in setsockopt function.\n");
		exit(EXIT_FAILURE);
	}
	return (serversocket);
}

int Server::bind_socket_to_port(char *argv, int serversocket)
{
	int addrlen;
	this->address_serv.sin_family = AF_INET;
	this->address_serv.sin_port = htons(atoi(argv));
	inet_pton(AF_INET, "0.0.0.0", &(this->address_serv.sin_addr));
	if (bind(serversocket, (sockaddr *)&(this->address_serv), sizeof(this->address_serv)) == -1)
	{
		perror("Error in bind.\n");
		return -1;
	}
	if (listen(serversocket, SOMAXCONN) == -1)
	{
		perror("Error in listen.\n");
		return -1;
	}
	addrlen = sizeof(this->address_serv);
	std::cout << "enter your password[PASS]" << std::endl;
	std::cout << "enter your nickname[NICK]" << std::endl;
	std::cout << "enter your username[USER]" << std::endl;
	std::cout << "Waiting for connections ..." << std::endl;
	return (addrlen);
}

void Server::send_all(std::string msg, Channel *ch, std::string nick)
{
	for (std::map<int, Client>::iterator it = client.begin(); it != client.end(); it++)
	{
		if (find(ch->users.begin(), ch->users.end(), &(it->second)) != ch->users.end())
		{
			if (send(it->first, msg.c_str(), msg.size(), 0) != (long)msg.size())
				this->send_msg("Error occured while sending msg", nick);
		}
	}
}

void Server::send_msg_to_all(std::string msg, Channel *ch, std::string nick)
{
	for (std::map<int, Client>::iterator it = client.begin(); it != client.end(); it++)
	{
		std::deque<Client *>::iterator it2 = find(ch->users.begin(), ch->users.end(), &(it->second));
		if (it2 != ch->users.end() && (*it2)->getNickName() != nick)
		{
			if (send(it->first, msg.c_str(), msg.size(), 0) != (long)msg.size())
				this->send_msg("Error occured while sending msg", nick);
		}
	}
}

void Server::send_msg(std::string msg, std::string nick)
{
	int fd = 0;

	for (std::map<int, Client>::iterator it = client.begin(); it != client.end(); it++)
	{
		if ((it->second).getNickName() == nick)
		{
			fd = it->first;
			break;
		}
	}
	if (fd != 0)
	{
		if (send(fd, msg.c_str(), msg.size(), 0) != (ssize_t)msg.size())
			perror("Error while sending message.\n");
	}
}
