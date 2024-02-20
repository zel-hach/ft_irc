/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by ssadiki           #+#    #+#             */
/*   Updated: 2023/08/03 22:37:47 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
    
}

Channel::Channel(const std::string& n):name(n), topic(""), mode("")
{
	key = "";
}

Channel::~Channel() {}

const std::string&  Channel::getName(void) const
{
    return (this->name);
}

const std::string&  Channel::getTopic(void) const
{
    return (this->topic);
}

const std::string&  Channel::getMode(void) const
{
    return (this->mode);
}

const std::string&  Channel::getKey(void) const
{
    return (this->key);
}

const std::string&  Channel::getLimit(void) const
{
    return (this->limit);
}
const std::string&  Channel::getOper(void) const
{
    return (this->oper);
}

void    Channel::setName(std::string& n)
{
    this->name = n;
}

void    Channel::setTopic(std::string& t)
{
    this->topic = t;
}

void    Channel::setMode(char m)
{
	this->mode.push_back(m);
}

void    Channel::unsetMode(char m)
{
    std::string::iterator it = std::find(mode.begin(),mode.end(),m);
    if (static_cast<std::string::size_type>(*it)!= std::string::npos)
	    this->mode.erase(it);
}

void    Channel::setKey(std::string k)
{
    this->key = k;
}

void    Channel::setLimit(std::string l)
{
    this->limit = l;
}
void    Channel::setOper(std::string l)
{
    this->oper = l;
}

