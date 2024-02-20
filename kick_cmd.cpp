/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:50 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/09 21:25:50 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void    split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &user_list, std::string& cmt)
{
	std::stringstream   ss(param);
	std::string     chs;
	std::string     users;

	getline(ss, chs, ' ');
	getline(ss, users, ' ');
	getline(ss, cmt);
	std::stringstream   ss_ch(chs);
	std::stringstream   ss_user(users);
	while(!ss_ch.eof())
	{
		std::string ch;
		getline(ss_ch, ch, ',');
		ch_list.push_back(ch);
	}
	while (!ss_user.eof())
	{
		std::string user;
		getline(ss_user, user, ',');
		user_list.push_back(user);
	}
}

Client*	getClient(std::string	user, Server& s)
{
	for (std::map<int, Client>::iterator it = s.client.begin(); it != s.client.end(); it++)
	{
		if (it->second.getNickName() == user)
			return &(it->second);
	}
	return (NULL);
}

void	kick_user(std::vector<std::string> ch_list, std::vector<std::string> users, std::string cmt, Client& c, Server& s)
{
	for (size_t i = 0; i < ch_list.size(); i++)
	{
		try{
			valid_ch(ch_list[i], c);
			int	ch_i = find_ch(ch_list[i], s);
			Client*	dest = getClient(users[i], s);

			if (ch_i < 0)
			{
				s.send_msg(ERR_NOSUCHCHANNEL(ch_list[i]),c.getNickName());
				return ;
			}
			Channel	*ch = s.chs[ch_i];
			if (find(ch->users.begin(), ch->users.end(), &c) == ch->users.end())
			{
				s.send_msg(ERR_NOTONCHANNEL(ch_list[i]),c.getNickName());
				return ;
			}
			if (find(ch->op.begin(), ch->op.end(), &c) == ch->op.end())
			{
				s.send_msg(ERR_CHANOPRIVSNEEDED(ch_list[i]),c.getNickName());
				return ;
			}
			if (find(ch->users.begin(), ch->users.end(), dest) == ch->users.end())
			{
				s.send_msg(ERR_USERNOTINCHANNEL(users[i],ch_list[i]),c.getNickName());
				return ;
			}
			s.send_all(PRE(c.getNickName(), c.user.getUser(), c.hostname) + " KICK " + ch->getName() + " " + dest->getNickName() + " " + cmt+ "\r\n", s.chs[ch_i], c.getNickName());
			if (find(ch->op.begin(), ch->op.end(), dest) != ch->op.end())
				ch->op.erase(find(ch->op.begin(), ch->op.end(), dest));
			ch->users.erase(find(ch->users.begin(), ch->users.end(), dest));
		}
		catch (std::string &str)
		{
			s.send_msg(str, c.getNickName());
		}
	}
}

void	kick_cmd(std::string param, Client& c, Server& s)
{
	std::vector<std::string>	ch_list;
	std::vector<std::string>	user_list;
	std::string					cmt;

	split_param(param, ch_list, user_list, cmt);
	if (ch_list[0].empty() || user_list[0].empty() || ch_list.size() != user_list.size())
	{
		std::string cmd = "KICK";
		s.send_msg(ERR_NEEDMOREPARAMS(cmd),c.getNickName());
		return ;
	}
	kick_user(ch_list, user_list, cmt, c, s);	
}
