/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:57 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/05 17:58:02 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int nickname_exist(Server server, std::string parametre, Client &cl)
{
    for (std::map<int, Client>::iterator it = server.client.begin(); it != server.client.end(); it++)
    {
        if (!(it->second.getNickName()).empty() && it->second.getNickName() == parametre)
        {
            if (cl.getNickName().empty())
                server.send_msg(ERR_NICKNAMEINUSE(parametre), cl.getNickName());
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
