/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:57 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/09 20:25:53 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::vector<std::string> ft_split(std::string str, char delim)
{
    std::vector<std::string> res;
    std::string wd;
    std::stringstream stream(str);

    for(; std::getline(stream, wd, delim); ){
        if (!wd.empty())
            res.push_back(wd);
    }
    return (res);
}

int nickname_exist(Server server, std::string parametre, Client &cl)
{
    for (std::map<int, Client>::iterator it = server.client.begin(); it != server.client.end(); it++)
    {
        if (!(it->second.getNickName()).empty() && it->second.getNickName() == parametre)
        {
            if (cl.getNickName().empty())
			{
                server.send_msg(ERR_NICKNAMEINUSE(parametre), cl.getNickName());
				cl.i = 0;
			}
            else
                 server.send_msg(ERR_NICKCOLLISION(cl.getNickName(),cl.user.getUser()), cl.getNickName());
            return (1);
        }
    }
    return (0);
}

void ft_strtrim(std::string &str)
{
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

std::string to_upper(std::string &str)
{
    int i;
    i = 0;
    std::string stri = str;
    while (stri[i])
    {
        stri[i] = toupper(stri[i]);
        i++;
    }
    return (stri);
}

int pars_mode_param(std::string &mode_param)
{
	const char *s;
	s = mode_param.c_str();
	for (unsigned long i = 0; i < mode_param.size(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

std::deque<Client *>::iterator find_user(std::string &mode_param, std::deque<Channel *>::iterator it)
{
	for (std::deque<Client *>::iterator it1 = (*it)->users.begin(); it1 != (*it)->users.end(); it1++)
	{
		if (((*it1)->getNickName() == mode_param))
			return (it1);
	}
	return ((*it)->users.end());
}
