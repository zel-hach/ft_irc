/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:12 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/08 19:12:31 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int f_index(std::string cmd)
{
	int i = -1;
	std::string cmds[] = {"JOIN", "MODE", "INVITE", "TOPIC", "KICK", "PRIVMSG", "NOTICE", "BOT"};
	while (++i <= 7)
	{
		if (cmd == cmds[i])
			return (i);
	}
	return (-1);
}

void    exec_ch_command(std::string& cmd, std::string& param, Client& cl, Server& serv)
{
	void    (*cmdsf[]) (std::string, Client&, Server&) = {&join_cmd, &mode_cmd, &invite_cmd, &topic_cmd, &kick_cmd, &prive_msg_cmd, &notice_cmd, &bot_cmd};

	switch (f_index(cmd))
	{
		case 0:
			cmdsf[0](param, cl, serv);
			break;
		case 1:
			cmdsf[1](param, cl, serv);
			break;
		case 2:
			cmdsf[2](param, cl, serv);
			break;
		case 3:
			cmdsf[3](param, cl, serv);
			break;
		case 4:
			cmdsf[4](param, cl, serv);
			break;
		case 5:
			cmdsf[5](param, cl, serv);
			break;
		case 6:
			cmdsf[6](param, cl, serv);
			break;
		case 7:
			cmdsf[7](param, cl, serv);
			break;
		default:
			serv.send_msg(":ircserv 421 " + cmd + " :Unknown command \r\n",cl.getNickName());
	}
}

bool	valid_ch(std::string& ch,Server &s,Client &c)
{
	if ((ch.find_first_of(CHANNEL_CHARS) != 0 || ch.size() > 50))
	{
		s.send_msg(ERR_NOSUCHCHANNEL(ch),c.getNickName());
		return (1);
	}
	for (size_t i = 0; i < ch.size(); i++)
	{
		if (ch[i] == ' ' || ch[i] == ',' || ch[i] == 7 || ch[i] == ':')
		{
			s.send_msg(ERR_NOSUCHCHANNEL(ch),c.getNickName());
			return (1);
		}
	}
	return (0);
}
