/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:45:04 by fabou-za          #+#    #+#             */
/*   Updated: 2023/08/09 21:26:03 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static void	split_param(std::string buff, std::vector<std::string> &split)
{
	std::vector<std::string> tmp;
	size_t pos = buff.find(":");
	if (pos != std::string::npos){
		tmp.push_back(buff.substr(0, pos));
		tmp.push_back(buff.substr(pos + 1));
	}
	else
		tmp.push_back(buff);
	split = ft_split(tmp[0], ' ');
	if (tmp.size() > 1)
		split.push_back(tmp[1]);
}

void notice_cmd(std::string param, Client &c, Server &s)
{
	std::vector<std::string> split;
	std::vector<std::string> recipient;

	split_param(param, split);
	if (split.size() == 0)
	{
		s.send_msg(ERR_NO_RECIPIENT_GIVEN(std::string("NOTICE")), c.getNickName());
		return ;
	}
	else if (split.size() == 1)
	{
		s.send_msg(ERR_NO_TEXT_TO_SEND(c.getNickName()), c.getNickName());
		return ;
	}
	else
	{
		recipient = ft_split(split[0], ',');
		std::vector<std::string>::iterator it = recipient.begin();
		for (; it != recipient.end(); it++)
		{
			if ((*it).find_first_of(CHANNEL_CHARS) == 0)
			{
				for (std::deque<Channel *>::iterator itr = s.chs.begin(); itr != s.chs.end(); itr++)
				{
					if ((*itr)->getName() == (*it))
					{
						s.send_all(PRE(c.getNickName(),c.user.getUser(),c.hostname) + " NOTICE " + *it + " :" + split[1] + "\r\n", (*itr), c.getNickName());
						break;
					}
				}
			}
			else
			{
				std::map<int, Client>::iterator itr;
				for (itr = s.client.begin(); itr != s.client.end(); itr++)
				{
					if ((*itr).second.getNickName() == (*it))
					{
						s.send_msg(PRE(c.getNickName(), c.user.getUser(),c.hostname) + " NOTICE " + *it + " :" + split[1] + "\r\n", *it);
						break;
					}
				}
			}
		}
	}
}
