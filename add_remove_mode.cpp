/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_remove_mode.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:43:02 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/10 15:00:06 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int add_mode(char str, std::vector<std::string> &mode_param, std::deque<Channel *>::iterator it, Server &server, Client &cl)
{
	switch (str)
	{
	case 'i':
		(*it)->setMode(str);
		break;
	case 't':
		(*it)->setMode(str);
		break;
	case 'l':
		if (mode_param.empty() || mode_param[0].empty())
		{
			server.send_msg(":ircserver 696 l * You must specify a parameter for the limit mode. Syntax: <limit> \r\n", cl.getNickName());
			return (0);
		}
		else if (pars_mode_param(mode_param[0]) == 1 && atoi(mode_param[0].c_str()) > (int)(*it)->users.size())
		{
			(*it)->setLimit(mode_param[0]);
			(*it)->setMode(str);
		}
		else
		{
			server.send_msg(":ircserver  696 l " + mode_param[0] + " Invalid limit mode parameter. Syntax: <limit>.\r\n", cl.getNickName());
			return (0);
		}
		break;
	case 'k':
		if (mode_param.empty() || mode_param[0].empty())
		{
			server.send_msg(":ircserver 696 k * You must specify a parameter for the key mode. Syntax: <key> \r\n", cl.getNickName());
			return (0);
		}
		else
		{
			(*it)->setKey(mode_param[0]);
			(*it)->setMode(str);
		}
		break;
	case 'o':
	{
		if (mode_param.empty() || mode_param[0].empty())
		{
			server.send_msg(":ircserver 696 o * You must specify a parameter for the op mode. Syntax: <nick> \r\n", cl.getNickName());
			return (0);
		}
		std::map<int, Client>::iterator	it_cl;
		for(it_cl = server.client.begin(); it_cl != server.client.end(); it_cl++)
		{
			if (it_cl->second.getNickName() == mode_param[0])
				break ;
		}
		if (it_cl == server.client.end())
		{
			server.send_msg(ERR_NOSUCHNICK(mode_param[0]), cl.getNickName());
			return (0);
		}
		std::deque<Client *>::iterator it1 = find_user(mode_param[0], it);
		if (it1 != (*it)->users.end())
		{
			if (find((*it)->op.begin(), (*it)->op.end(), (*it1)) == (*it)->op.end())
			{
				(*it)->op.push_back((*it1));
				(*it)->setOper(mode_param[0]);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	break;
	default:
		server.send_msg(":ircserver 472 " + std::string(1, str) + " :is unknown mode char to me for " + (*it)->getName() + "\r\n", cl.getNickName());
		return (0);
		break;
	}
	return (1);
}

int remove_mode(char str, std::vector<std::string> &mode_param, std::deque<Channel *>::iterator it, Server &s, Client &cl)
{
	if (str == 'k' || str == 'l' || str == 't' || str == 'i')
	{
		if (str == 'k')
		{
			(*it)->old_key = (*it)->getKey();
			(*it)->setKey(" ");
		}
		if (str == 'l')
		{
			(*it)->old_limit = (*it)->getLimit();
			(*it)->setLimit(" ");
		}
		(*it)->unsetMode(str);
	}
	else if (str == 'o')
	{
		if (mode_param.empty() || mode_param[0].empty())
		{
			s.send_msg(":ircserver 696 o * You must specify a parameter for the op mode. Syntax: <nick> \r\n", cl.getNickName());
			return (0);
		}
		std::map<int, Client>::iterator	it_cl;
		for(it_cl = s.client.begin(); it_cl != s.client.end(); it_cl++)
		{
			if (it_cl->second.getNickName() == mode_param[0])
				break;
			
		}
		if (it_cl == s.client.end())
		{
			s.send_msg(ERR_NOSUCHNICK(cl.getNickName()), cl.getNickName());
			return (0);
		}
		for (std::deque<Client *>::iterator it1 = (*it)->op.begin(); it1 != (*it)->op.end(); it1++)
		{
			if ((*it1)->getNickName() == mode_param[0])
			{
				(*it)->setOper(mode_param[0]);
				(*it)->op.erase(it1);
				return (1);
			}
		}
		return (0);
	}
	else
	{
		s.send_msg(":472 " + std::string(1, str) + " :is unknown mode char to me for " + (*it)->getName() + "\r\n", cl.getNickName());
		return (0);
	}
	return (1);
}
