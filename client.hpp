/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:02 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/08 19:17:09 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"
#include "Channel.hpp"
#include "commands.hpp"
#include <poll.h>
#include <utility>
#include "replies.hpp"

class User;
class Server;
class Channel;
class Client
{
private:
	std::string 		user_name;
	std::string 		nickname;
	bool				flag;
	int 				pass;
public:
	struct sockaddr_in	address_client;
	char 				hostname[50];
	int					addrlen;
	User 				user;
	int 				len;
	int 				i;
	bool				enter;
	Client();
	~Client();
	Client(const Client &);
	Client 				&operator=(const Client &);

	int 				getPass();
	std::string 		getNickName(void);

	void 				setPass(int);
	void 				setNickName(std::string);

	std::vector<pollfd> connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Server &server);
	void 				send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index, Server &server);
	void				parse_ch_cmd(std::string, std::string, Server&);
};

std::string 			to_upper(std::string &str);
int 					nickname_exist(Server server, std::string parametre,Client &cl);
void 					ft_strtrim(std::string &str);
std::vector<std::string> ft_split(std::string str, char delim);
#endif
