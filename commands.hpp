/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:23 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/10 11:49:29 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Channel.hpp"

void	exec_ch_command(std::string&, std::string&, Client&, Server&);

void	join_cmd(std::string, Client&, Server&);
void	topic_cmd(std::string, Client&, Server&);
void	invite_cmd(std::string, Client&, Server&);
void	mode_cmd(std::string, Client&, Server&);
void	kick_cmd(std::string, Client&, Server&);
void	user_cmd(std::string, Client&, Server&);
void 	prive_msg_cmd(std::string param, Client &c, Server &s);
void	notice_cmd(std::string, Client&, Server&);
void    bot_cmd(std::string, Client&, Server&);

void		valid_ch(std::string& ch, Client&);
bool	valid_ch(std::string &);
int		find_ch(std::string ch, Server& s);
Client*	getClient(std::string, Server&);
void 	send_msg_in_channel(Server &server,Client &cl,Channel &ch);
void 	cmd_user(std::string &parametre,Client &cl, Server &server,std::string command);
void 	cmd_nick(std::string &parametre, Client &cl, Server &server);
void 	cmd_pass(std::string &parametre,Client &cl, Server &server,std::string command, char *argv);
int 	pars_mode_param(std::string &mode_param);
int 	add_mode(char str, std::vector<std::string> &mode_param, std::deque<Channel *>::iterator it, Server &server, Client &cl);
int 	remove_mode(char str, std::vector<std::string> &mode_param, std::deque<Channel *>::iterator it, Server &s, Client &cl);
std::deque<Client *>::iterator find_user(std::string &mode_param, std::deque<Channel *>::iterator it);
void 	affiche_add_mode(std::string &mode, std::deque<Channel *>::iterator it, Server &server, Client &cl);
void 	affiche_remove_mode(std::string &mode, std::deque<Channel *>::iterator it, Server &server, Client &cl);
#endif
