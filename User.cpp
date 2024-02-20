/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:17 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/08 13:27:26 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User:: User()
{

}
User:: ~User()
{

}
void User:: setUser(const std::string user)
{
    this->user = user;
}
void User:: setMode(const std::string  mode)
{
    this->mode = mode;
}
void User:: setUnused(const std::string  unused)
{
    this->unused = unused;
}
void User:: setRealname(const std::string realname)
{
    this->realname = realname;
}

std::string  & User :: getUser(void)
{
    return (this->user);
}
std::string & User :: getMode(void)
{
    return (this->mode);
}
std::string & User :: getUnused(void)
{
    return (this->unused);
}
std::string & User :: getRealname(void)
{
    return (this->realname);
}