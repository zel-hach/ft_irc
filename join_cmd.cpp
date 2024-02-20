/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:29 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/09 21:24:14 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &key_list)
{
	std::stringstream ss(param);
	std::string chs;
	std::string keys;

	getline(ss, chs, ' ');
	getline(ss, keys);
	std::stringstream ss_ch(chs);
	std::stringstream ss_key(keys);

	while (!ss_ch.eof())
	{
		std::string ch;
		getline(ss_ch, ch, ',');
			ch_list.push_back(ch);
	}
	while (!ss_key.eof())
	{
		std::string key;
		getline(ss_key, key, ',');
		key_list.push_back(key);
	}
}

void valid_ch(std::string& ch, Client &c)
{
	if (((ch.find_first_of(CHANNEL_CHARS) != 0 || ch.size() > 50) || ch.size() == 1) && ch != "0")
	{
		throw(ERR_BADCHANMASK(ch));
	}
	for (size_t i = 0; i < ch.size(); i++)
	{
		if (ch[i] == ' ' || ch[i] == ',' || ch[i] == 7 || ch[i] == ':' || ch[i] == '*')
		{
			throw(ERR_BADCHANMASK(ch), c.getNickName());
		}
	}
}

int find_ch(std::string ch, Server &s)
{
	for (unsigned long i = 0; i < s.chs.size(); i++)
	{
		if (s.chs[i]->getName() == ch)
		{
			return (i);
		}
	}
	return (-1);
}

int check_modes(Channel ch, Client &c)
{
	if (find(ch.invite.begin(), ch.invite.end(), &c) == ch.invite.end())
	{
		if ((ch.getMode()).find('i') != std::string::npos)
			throw(ERR_INVITEONLYCHAN(ch.getName()));
		if ((ch.getMode()).find('l') != std::string::npos && (int)ch.users.size() >= atoi((ch.getLimit()).c_str()))
		{
			throw(ERR_CHANNELISFULL(ch.getName()));
		}
	}
	if ((ch.getMode()).find('k') != std::string::npos)
		return (1);
	return (0);
}

void add_user(std::string ch, std::vector<std::string> &key_list, int i, Client &c, Server &s)
{
	int ch_i = find_ch(ch, s);

	try
	{
		if (find(s.chs[ch_i]->users.begin(), s.chs[ch_i]->users.end(), &c) == s.chs[ch_i]->users.end())
		{
			int k = check_modes(*s.chs[ch_i], c);
			std::deque<Client *> &invite = s.chs[ch_i]->invite;
			if (find(invite.begin(), invite.end(), &c) == invite.end())
			{
				if (k && key_list[i] != s.chs[ch_i]->getKey())
					throw(ERR_BADCHANNELKEY(ch));
			}
			else
				s.chs[ch_i]->invite.erase(find(invite.begin(), invite.end(), &c));
			s.chs[ch_i]->users.push_back(&c);
			s.send_all(":" + c.getNickName() + "!" + c.user.getUser() + "@" + c.hostname + " JOIN " + ch + "\r\n", s.chs[ch_i], c.getNickName());
		}
		if ((s.chs[ch_i]->getMode()).find("k") != std::string::npos)
			s.send_msg(": 353 " + c.getNickName() + " + " + ch + " :" + c.getNickName(), c.getNickName());
		else
			s.send_msg(": 353 " + c.getNickName() + " = " + ch + " :" + c.getNickName(), c.getNickName());
		for (std::deque<Client *>::iterator it = s.chs[ch_i]->users.begin(); it != s.chs[ch_i]->users.end(); it++)
		{
			if (find(s.chs[ch_i]->op.begin(), s.chs[ch_i]->op.end(), (*it)) != s.chs[ch_i]->op.end())
				s.send_msg(" @" + (*it)->getNickName(), c.getNickName());
			else
				s.send_msg(" " + (*it)->getNickName(), c.getNickName());
		}
		s.send_msg("\r\n", c.getNickName());
		s.send_msg(RPL_ENDOFNAMES(ch), c.getNickName());
	}
	catch (std::string &str)
	{
		throw(str);
	}
}

void create_ch(std::string ch, std::string key, Client &c, Server &s)
{
	Channel *n_ch = new Channel(ch);

	n_ch->users.push_back(&c);
	n_ch->op.push_back(&c);
	s.send_all(":" + c.getNickName() + "!" + c.user.getUser() + "@" + c.hostname + " JOIN " + ch + "\r\n", n_ch, c.getNickName());
	if (!key.empty())
	{
		n_ch->setKey(key);
		n_ch->setMode('k');
		s.send_msg(": 353 " + c.getNickName() + " + " + ch + " :" + c.getNickName() + " @" + c.getNickName() + "\r\n", c.getNickName());
	}
	else
		s.send_msg(": 353 " + c.getNickName() + " = " + ch + " :" + c.getNickName() + " @" + c.getNickName() + "\r\n", c.getNickName());
	s.send_msg(RPL_ENDOFNAMES(ch), c.getNickName());
	s.chs.push_back(n_ch);
}

void quit_all(Client &c, Server &s)
{
	for (std::deque<Channel *>::iterator it = s.chs.begin(); it != s.chs.end(); it++)
	{
		std::deque<Client *> &users = (*it)->users;
		for (std::deque<Client *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
		{
			if (*it2 == &c)
			{
				s.send_all(":" + c.getNickName() + " PART " + (*it)->getName() + "\r\n", (*it), c.getNickName());
				users.erase(it2);
				break;
			}
		}
	}
}

int join_ch(std::vector<std::string> &ch_list, std::vector<std::string> &key_list, Client &c, Server &s)
{
	for (unsigned long i = 0; i < ch_list.size(); i++)
	{
		try
		{
			valid_ch(ch_list[i], c);
			if (ch_list[i] == "0")
				quit_all(c, s);
			else if (!s.chs.empty() && find_ch(ch_list[i], s) >= 0)
				add_user(ch_list[i], key_list, i, c, s);
			else
				create_ch(ch_list[i], key_list[i], c, s);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (std::string &str)
		{
			s.send_msg(str, c.getNickName());
		}
	}
	return (0);
}

void join_cmd(std::string param, Client &c, Server &s)
{
	std::vector<std::string> ch_list;
	std::vector<std::string> key_list;


	split_param(param, ch_list, key_list);
	if (ch_list[0].empty())
	{
		std::string cmd = "JOIN";
		s.send_msg(ERR_NEEDMOREPARAMS(cmd), c.getNickName());
		return;
	}
	join_ch(ch_list, key_list, c, s);
}
