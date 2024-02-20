/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:14:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/10 14:48:57 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"
#include <vector>
#include "Channel.hpp"

void set_mode(std::string &str, std::string &mode_param, std::deque<Channel *>::iterator it, Server &server, Client &cl)
{
	const char *s;
	int j = 0;
	std::string mode;
	std::vector<std::string> params_m = ft_split(mode_param, ' ');

	s = str.c_str();
	for (unsigned long i = 1; i < str.size(); i++)
	{
		switch (s[0])
		{
		case '+':
		{
			if ((*it)->getMode().find(str[i]) == std::string::npos)
			{
				j = 1;
				if (add_mode(s[i], params_m, it, server, cl) != 0)
					mode.append(std::string(1, str[i]));
			}
			if (!params_m.empty() && str[i] != 't' && str[i] != 'i')
				params_m.erase(params_m.begin());
		}
		break;
		case '-':
		{
			if ((*it)->getMode().find(str[i]) != std::string::npos  || str[i] == 'o')
			{
				j = 2;
				if (remove_mode(s[i], params_m, it, server, cl) != 0)
					mode.append(std::string(1, str[i]));
			}
			if (!params_m.empty() && str[i] != 't' && str[i] != 'i')
				params_m.erase(params_m.begin());
			break;
		}
		default:
			break;
		}
	}
	if (j == 1 && !mode.empty())
		affiche_add_mode(mode, it, server, cl);
	else if (j == 2 && !mode.empty())
		affiche_remove_mode(mode, it, server, cl);
}

void mode_cmd(std::string param, Client &c, Server &s)
{
	std::stringstream str(param);
	std::string mode;
	std::string channel;
	std::string modeparam;

	getline(str, channel, ' ');
	getline(str, mode, ' ');
	getline(str, modeparam);
	if (channel.empty())
	{
		s.send_msg(":461 MODE :Not enough parameters\r\n", c.getNickName());
		return;
	}
	for (std::deque<Channel *>::iterator it = s.chs.begin(); it != s.chs.end(); it++)
	{
		std::deque<Client *>::iterator it_op = std::find((*it)->op.begin(), (*it)->op.end(), &c);
		if ((*it)->getName() == channel)
		{
			std::deque<Client *>::iterator it_user = std::find((*it)->users.begin(), (*it)->users.end(), &c);
			if (it_user != (*it)->users.end())
			{
				if (mode.empty())
				{
					std::string str;
					const char * c_str = (*it)->getMode().c_str();	
					for (int i = 0;i < (int)(*it)->getMode().size(); i++)
					{
						if (c_str[i] != 'o')
							str.append(std::string(1,c_str[i]));
					}
					std::sort(str.begin(), str.end());
					s.send_msg(RPL_CHANNELMODEIS(c.getNickName(), channel, str, (*it)->getKey() + " " + (*it)->getLimit()), c.getNickName());
					return;
				}
				if (it_op != (*it)->op.end())
					set_mode(mode, modeparam, it, s, c);
				else
					s.send_msg(ERR_CHANOPRIVSNEEDED((*it)->getName()), c.getNickName());
			}
			else
				s.send_msg(ERR_NOTONCHANNEL((*it)->getName()), c.getNickName());
			return;
		}
	}
	s.send_msg(ERR_NOSUCHCHANNEL(channel), c.getNickName());
}
