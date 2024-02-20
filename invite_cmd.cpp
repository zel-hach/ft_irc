/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:28:33 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/03 16:13:15 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void	invite_user(std::string nick, std::string ch, Client& c, Server& s)
{
	int	ch_i = find_ch(ch, s);

	if (ch_i < 0)
	{
		s.send_msg(ERR_NOSUCHCHANNEL(ch),c.getNickName());
		return ;
	}
	Channel*	ch2 = s.chs[ch_i];
	if (find(ch2->users.begin(), ch2->users.end(), &c) == ch2->users.end())
	{
		s.send_msg(ERR_NOTONCHANNEL(ch),c.getNickName());
		return ;
	}
	Client	*dest = getClient(nick, s);
	if (dest == NULL)
	{
		s.send_msg(ERR_NOSUCHNICK(nick),c.getNickName());
		return ;
	}
	if (find(ch2->users.begin(), ch2->users.end(), dest) != ch2->users.end())
	{
		s.send_msg(ERR_USERONCHANNEL(nick, ch), c.getNickName());
		return ;
	}
	if (ch2->getMode().find('i') != std::string::npos && find(ch2->op.begin(), ch2->op.end(), &c) == ch2->op.end())
	{
		s.send_msg(ERR_CHANOPRIVSNEEDED(ch), c.getNickName());
		return ;
	}
	ch2->invite.push_back(dest);
	s.send_msg(PRE(c.getNickName(),c.user.getUser(),c.hostname) + " INVITE " + dest->getNickName() + " " + ch + "\r\n", dest->getNickName());
	s.send_msg(RPL_INVITING(ch, dest->getNickName(), c.getNickName(), c.user.getUser(), c.hostname), c.getNickName());
}

void	invite_cmd(std::string param, Client& c, Server& s)
{
	std::stringstream	ss(param);
	std::string			nick;
	std::string			ch;

	getline(ss, nick, ' ');
	getline(ss, ch);

	if (nick.empty() || ch.empty())
	{
		s.send_msg(ERR_NEEDMOREPARAMS(std::string("INVITE")), c.getNickName());
		return ;
	}
	invite_user(nick, ch, c, s);
}
