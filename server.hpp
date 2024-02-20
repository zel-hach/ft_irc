/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:36:01 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/08 18:52:31 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <map>
#include <deque>
#include <vector>
#include "client.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <fcntl.h>

class User;
class Client;
class Channel;
class Server
{
public:
	int                 	serversocket;
	struct sockaddr_in		address_serv;
	std::map<int, Client> 	client;
	std::deque<Channel *> 	chs;
	Server();
	~Server();
	Server(Server &);
	Server 					&operator=(Server &);
	int 					create_socket();
	int 					bind_socket_to_port(char *argv, int serversocket);
	void 					send_all(std::string, Channel *, std::string);
	void 					send_msg_to_all(std::string, Channel *, std::string);
	void 					send_msg(std::string, std::string);
};

#endif
