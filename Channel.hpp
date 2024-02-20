/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:01 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/04 13:27:27 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#define CHANNEL_CHARS "&#+|"
#define CHANNEL_MODS "klito"
#include "client.hpp"
#include "server.hpp"
#include <deque>
#include <algorithm>

class Server;
class Client;
class Channel{
	std::string name;
	std::string key;
	std::string	limit;
	std::string topic;
	std::string mode;
	std::string oper;
	public:
		std::deque<Client *> op;
		std::deque<Client *> invite;
		std::deque<Client *> users;
		std::vector<std::string> msgs_channel;
		std::string old_key;
		std::string old_limit;
		std::string mode_str;
		Channel();
		Channel(const std::string&);
		~Channel();
		const std::string&	getName(void) const;
		const std::string&	getTopic(void) const;
		const std::string&	getMode(void) const;
		const std::string&	getKey(void) const;
		const std::string&	getLimit(void) const;
		const std::string&	getOper(void) const;
		void				setName(std::string&);
		void				setTopic(std::string&);
		void				setMode(char);
		void				unsetMode(char);
		void				setKey(std::string);
		void				setLimit(std::string);
		void				setOper(std::string);

};

#endif
