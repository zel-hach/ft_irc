/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:35:02 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/09 12:17:41 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP 
#include <iostream>
#include "Channel.hpp"

#define RPL_WHOISOPERATOR(nick) (":ircserver 313 " + nick + " :is an IRC operator\r\n")
#define RPL_CHANNELMODEIS(nick, ch,mode,mp) (":ircserver 324 " + nick + " " + ch + " +" + mode + " " + mp + "\r\n")
#define RPL_NOTOPIC(nick,ch) (":ircserver 331 " + nick + ch + " :No topic is set\r\n")
#define RPL_TOPIC(nick, ch,topic) (":ircserver 332 " + nick + " " + ch + " :" + topic + "\r\n")
#define RPL_INVITING(ch,dest,nick,user,host) (":ircserver 341 " + nick + " " + dest + " " + ch + "\r\n")
#define RPL_ENDOFNAMES(ch) (":ircserver 366 " + ch + " :End of NAMES list\r\n")
#define ERR_NOSUCHNICK(nick) (":ircserver 401 " + nick + " :No such nick/channel\r\n")
#define ERR_NOSUCHCHANNEL(ch) (":ircserver 403 "  + ch + " :No such channel\r\n")
#define ERR_TOOMANYCHANNELS(ch) (":ircserver 405 " + ch + " :You have joined too many channels\r\n")
#define ERR_NO_RECIPIENT_GIVEN(cmd) (":ircserver 411 :No recipient given " + cmd + "\r\n")
#define ERR_NO_TEXT_TO_SEND(nick) (":ircserver 412 " + nick + " :No text to send\r\n")
#define ERR_NONICKNAMEGIVEN() (":ircserver 431 No nickname given\r\n")	
#define ERR_ERRONEUSNICKNAME(nick) (":ircserver 432 " + nick + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (":ircserver 433 " + nick + " :Nickname is already in use\r\n")
#define ERR_NICKCOLLISION(nick,user) (":ircserver 436 " + nick + " :Nickname collision KILL from " + user + "@localhost\r\n")
#define ERR_USERNOTINCHANNEL(nick,ch) (":ircserver 441 " + nick + " " + ch + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(ch) (":ircserver 442 " + ch + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(nick,ch) (":ircserver 443 " + nick + ch + " :is already on channel\r\n")
#define ERR_NOTREGISTERED() (":ircserver 451 You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(cmd) (":ircserver 461 " + cmd + " :Not enough parameters\r\n")
#define ERR_NOT_ENOUGH_PARAMS(nick) (":ircserver 461 " + nick + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED() (":ircserver 462 Unauthorized command (already registered)\r\n")
#define ERR_PASSWDMISMATCH() (":ircserver 464 Password incorrect\r\n")
#define ERR_KEYSET(ch) (":ircserver 467 " + ch + " :Channel key already set\r\n")
#define ERR_CHANNELISFULL(ch) (":ircserver 471 " + ch + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(ch) (":ircserver 473 " + ch + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(ch) (":ircserver 475 " + ch + " :Cannot join channel (+k)\r\n")
#define ERR_BADCHANMASK(ch) (":ircserver 476 " + ch + " :Bad Channel Mask\r\n")
#define ERR_CHANOPRIVSNEEDED(ch) (":ircserver 482 " + ch + " :You're not channel operator\r\n")
#define PREFIX(nick) ( ":" + nick)
#define PRE(nick,user,host) (":" + nick + "!" + user + "@" + host)
#define RPL_NICKCHANGE(old, new_n)(":" + old + " NICK " + new_n + "\r\n")
#define RPL_WELCOME(nick, user,hostname) (":ircserver 001 " + nick + " !" + user + " @" + hostname + " Welcome to the Internet Relay Network\r\n")

#endif
