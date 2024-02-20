/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_cmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:34:07 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/09 17:24:38 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void    bot_cmd(std::string param, Client& c, Server& s)
 {
     if (to_upper(param) != "HELP")
	 {
         s.send_msg(": 421 BOT " + to_upper(param) + " Unknown command\r\n", c.getNickName());
		 return ;
	 }
	s.send_msg(": 372 " + c.getNickName() + " The commands available in our server are as follow:\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " JOIN <channel> [key]\r\n", c.getNickName());
	s.send_msg(": 372" + c.getNickName() + " \t This command is used to join a already existing channel or create it if it does not exist. You can also join a list of channel in one time of course with their correspending key if any.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " INVITE <nickname> <channel>\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t This command is used to invite a user to a channel you are a member of. Unlike JOIN and KICK you can only invite one user at a time.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " KICK <channel> <nickname>\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t This command makes you kick a member or more from a channel. Of course you must an operator/admin to be able to execute this operation.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " TOPIC <channel> [topic]\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t This command makes you change the topic of the channel or if no topic is given, shows you the current topic\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " MODE <channel> [ +/- <mods> [mode_params] ]\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + "\t This command is used to change the mode of the channel or if no mods are given, shows you the current mode.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t The available mods are as follow:\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t\t k to set the key for channel\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t\t l to set the limit number of members in channel\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t\t i to set channel as invite only.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t\t t to make topic updatable only by operators.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t\t o to upgrade a member to operator.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " \t All these operations can of course only be executed by a channel operator/admin.\r\n", c.getNickName());
	s.send_msg(": 372 " + c.getNickName() + " This is the end of the help menu please consider asking the moderators of the project for more informtaions.\r\n", c.getNickName());
}
