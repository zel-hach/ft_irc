/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:21:41 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/09 12:18:26 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int valide_nickname(std::string nickname)
{
	int i;
	const char *str;

	str = nickname.c_str();
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= '[') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '_' || str[i] == ']')
		{
			if (i == 0 && (str[i] >= '0' && str[i] <= '9'))
				return (1);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

void cmd_user(std::string &parametre, Client &cl, Server &server, std::string command)
{
	User user;
	char *us;
	us = strtok((char *)parametre.c_str(), " ");
	if (us)
		user.setUser(std::string(us));
	us = strtok(NULL, " ");
	if (us)
		user.setMode(std::string(us));
	us = strtok(NULL, " ");
	if (us)
		user.setUnused(std::string(us));
	us = strtok(NULL, " ");
	if (us)
		user.setRealname(std::string(us));
	if (user.getRealname().empty() || user.getMode().empty() || user.getUnused().empty() || user.getUser().empty())
		server.send_msg(ERR_NEEDMOREPARAMS(command), cl.getNickName());
	else if (cl.len == 1)
		server.send_msg(ERR_ALREADYREGISTRED(), cl.getNickName());
	else
	{
		cl.user = user;
		cl.len++;
	}
}

void cmd_nick(std::string &parametre, Client &cl, Server &server)
{
	if (parametre.length() == 0)
		server.send_msg(ERR_NONICKNAMEGIVEN(), cl.getNickName());
	else if (valide_nickname(parametre) == 1)
		server.send_msg(ERR_ERRONEUSNICKNAME(parametre), cl.getNickName());
	else
	{
		cl.setNickName(parametre);
		cl.i = 1;
	}
}

void cmd_pass(std::string &parametre, Client &cl, Server &server, std::string command, char *argv)
{
	if (parametre == "\0")
		server.send_msg(ERR_NEEDMOREPARAMS(command), cl.getNickName());
	else if (cl.getPass() == 1)
		server.send_msg(ERR_ALREADYREGISTRED(), cl.getNickName());
	else if (parametre == argv || std::string(argv) == "")
		cl.setPass(1);
}

