/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/09 14:26:31 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
	this->i = 0;
	this->len = 0;
	flag = 0;
	this->enter = 0;
	this->pass = 0;
}

Client::~Client() {}

Client::Client(const Client &cp)
{
	*this = cp;
}

Client &Client::operator=(const Client &cpy)
{
	if (this != &cpy)
	{
		this->pass = cpy.pass;
		this->user_name = cpy.user_name;
		this->nickname = cpy.nickname;
		this->flag = cpy.flag;
	}
	return (*this);
}

int Client::getPass()
{
	return (this->pass);
}

std::string Client::getNickName(void)
{
	return (this->nickname);
}

void Client::setPass(int pass)
{
	this->pass = pass;
}

void Client::setNickName(std::string nick_name)
{
	this->nickname = nick_name;
}

std::vector<pollfd> Client::connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Server &server)
{
	int new_socket;
	char message[21] = "welcome to client \n";
	if ((new_socket = accept(serversocket,
							 (struct sockaddr *)&this->address_client, (socklen_t *)&(this->addrlen))) < 0)
	{
		perror("Error in accept.\n");
		exit(EXIT_FAILURE);
	}
	std::cout << "New connection , socket fd is  " << new_socket << ", ip is : " << inet_ntoa(this->address_client.sin_addr) << ", port : " << ntohs(this->address_client.sin_port) << "\n";
	size_t k;
	if ((k = send(new_socket, message, strlen(message), 0)) != strlen(message))
		perror("Error in send.\n");
	std::cout << "Welcome message sent successfully\n";
	pollfd p;
	p.fd = new_socket;
	p.events = POLLIN;
	readfds.push_back(p);
	server.client[p.fd] = *this;
	return (readfds);
}

void Client::send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index, Server &server)
{

	char buffer[1024];
	std::string line;

	memset(buffer, 0, sizeof(buffer));
	int valread;
	while ((valread = read(readfds[*index].fd, buffer, 1)) >= 1 && buffer[0] != '\n')
		line.append(buffer);
	if (valread <= 0)
	{
		std::cout << "Host disconnected .\n";
		close(readfds[*index].fd);
	}
	else
	{
		std ::stringstream str(line);
		std::string command;
		std::string parametre;

		getline(str, command, ' ');
		getline(str, parametre);
		ft_strtrim(parametre);
		ft_strtrim(command);
		command = to_upper(command);
		std::string old = this->nickname;

		if (command == "PASS" && this->enter == 0)
			cmd_pass(parametre, *this, server, command, argv);
		if (command == "NICK" && this->getPass() == 1)
		{
			if (nickname_exist(server, parametre, (*this)) == 0)
				cmd_nick(parametre, *this, server);
			else
				return;
		}
		if (command == "USER" && this->getPass() == 1 && this->enter == 0)
		{
			if (this->i == 1)
				cmd_user(parametre, *this, server, command);
			else
				server.send_msg(": 451 you have not registred. Please enter your nickname first.\r\n", this->getNickName());
		}
		if (!this->flag && this->i == 1 && this->len == 1)
		{
			int rc = gethostname(this->hostname, sizeof(this->hostname));
			if (rc != 0)
				perror("hostname");
			std::cout << "A user is connected  with nickname : " << this->nickname << std::endl;
			server.send_msg(":ircserver 372 " + this->getNickName() + " __ ____ __ ___  __   ____ ____  __ __\r\n", this->getNickName());
			server.send_msg(":ircserver 372 " + this->getNickName() + " || || \\  //   (( \\ ||    || \\ || ||\r\n", this->getNickName());
			server.send_msg(":ircserver 372 " + this->getNickName() + " || ||_// ((     \\  ||==  ||_// \\ //\r\n", this->getNickName());
			server.send_msg(":ircserver 372 " + this->getNickName() + " || || \\  \\__ \\_)) ||___ || \\  \\V/\r\n", this->getNickName());
			server.send_msg(RPL_WELCOME(this->getNickName(), this->user.getUser(), hostname), this->getNickName());
			this->flag = 1;
			this->enter = 1;
		}
		else if (command == "NICK" && this->i > 1 && this->len == 1)
			server.send_msg(RPL_NICKCHANGE(old, parametre), this->getNickName());
		else if (command != "NICK" && this->flag)
			parse_ch_cmd(command, parametre, server);
	}
}

void Client::parse_ch_cmd(std::string cmd, std::string param, Server &server)
{
	if (cmd == "JOIN" || cmd == "MODE" || cmd == "INVITE" || cmd == "TOPIC" || cmd == "KICK" || cmd == "PRIVMSG" || cmd == "NOTICE" || cmd == "BOT")
		exec_ch_command(cmd, param, *this, server);
	else
	{
		server.send_msg(":ircserver 421  " + cmd + " Unknown command \r\n", this->getNickName());
		return;
	}
}
