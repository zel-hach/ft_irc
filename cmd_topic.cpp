/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:26:05 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/08 19:12:46 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replies.hpp"

void topic_cmd(std::string param, Client &c, Server &s)
{
	std::stringstream str(param);
	std::string topic;
	std::string channel;
	getline(str, channel, ' ');
	getline(str, topic);

	if (param.empty())
	{
		s.send_msg(ERR_NEEDMOREPARAMS(std::string("TOPIC")), c.getNickName());
		return ;
	}
	if (channel.at(0) == ':')
	{
		s.send_msg(":ircserver 403 " + c.getNickName() + channel + " :No such channel\r\n", c.getNickName());
		return;
	}
	for (std::deque<Channel *>::iterator it = s.chs.begin(); it != s.chs.end(); it++)
	{
		if ((*it)->getName() == channel)
		{
			std::deque<Client *>::iterator it_user = std::find((*it)->users.begin(), (*it)->users.end(), &c);
			if (it_user == (*it)->users.end())
				s.send_msg(ERR_NOTONCHANNEL((*it)->getName()), c.getNickName());
			else
			{
				if (!topic.empty())
				{
					if (((*it)->getMode()).find('t') != std::string::npos)
					{
						if ((std::find((*it)->op.begin(), (*it)->op.end(), &c) == (*it)->op.end()))
						{
							s.send_msg(ERR_CHANOPRIVSNEEDED((*it)->getName()), c.getNickName());
							return ;
						}
					}
					if (topic[0] == ':')
						topic.erase(0, 1);
					(*it)->setTopic(topic);
					s.send_all(PRE(c.getNickName(), c.user.getUser(), c.hostname)  + " TOPIC " + (*it)->getName() + " :" + (*it)->getTopic() + "\r\n", *it, c.getNickName());
					return ;
				}
				if ((*it)->getTopic().empty())
					s.send_msg(RPL_NOTOPIC(c.getNickName(),(*it)->getName()), c.getNickName());
				else
					s.send_msg(RPL_TOPIC(c.getNickName(),(*it)->getName(), (*it)->getTopic()), c.getNickName());
			}
			return ;
		}
	}
	s.send_msg(ERR_NOSUCHCHANNEL(channel),c.getNickName());
}
