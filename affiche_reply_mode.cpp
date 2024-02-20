/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche_reply_mode.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:45:41 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/10 11:50:33 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void affiche_add_mode(std::string &mode, std::deque<Channel *>::iterator it, Server &server, Client &cl)
{
	server.send_all(PRE(cl.getNickName(), cl.user.getUser(), cl.hostname) + " MODE " + (*it)->getName() + " +" + mode, (*it), cl.getNickName());
	for (int i = 0; i < (int)mode.size(); i++)
	{
		if (mode[i] == 'k')
			server.send_all(" " + (*it)->getKey(), (*it), cl.getNickName());
		if (mode[i] == 'l')
			server.send_all(" " + (*it)->getLimit(), (*it), cl.getNickName());
		if (mode[i] == 'o')
			server.send_all(" " + (*it)->getOper(), (*it), cl.getNickName());
	}
	server.send_all("\r\n", (*it), cl.getNickName());
}

void affiche_remove_mode(std::string &mode, std::deque<Channel *>::iterator it, Server &server, Client &cl)
{
	server.send_all(PRE(cl.getNickName(), cl.user.getUser(), cl.hostname) + " MODE " + (*it)->getName() + " -" + mode, (*it), cl.getNickName());
	for (int i = 0; i < (int)mode.size(); i++)
	{
		if (mode[i] == 'k')
			server.send_all(" " + (*it)->old_key, (*it), cl.getNickName());
		if (mode[i] == 'l')
			server.send_all(" " + (*it)->old_limit, (*it), cl.getNickName());
		if (mode[i] == 'o')
			server.send_all(" " + (*it)->getOper(), (*it), cl.getNickName());
	}
	server.send_all("\r\n", (*it), cl.getNickName());
}
