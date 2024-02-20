/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:09 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/10 11:48:57 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"
#include "User.hpp"
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>

std::vector<pollfd>::iterator find_pollfd(std::vector<pollfd> &readfds, pollfd &value)
{
    for (std::vector<pollfd>::iterator it = readfds.begin(); it != readfds.end(); it++)
    {
        if (&(*it) == &value)
            return (it);
    }
    return (readfds.end());
}

int argv_is_digit(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' && str[i] > '9')
            return (0);
    }
    return (1);
}

void clear_client(int index, Server &server, std::vector<pollfd> &readfds)
{
    std::cout << "Client with fd : " << readfds[index].fd << " disconnected." << std::endl;
    for (std::deque<Channel *>::iterator it = server.chs.begin(); it != server.chs.end(); it++)
    {
        if (std::find((*it)->users.begin(), (*it)->users.end(), &(server.client[readfds[index].fd])) != (*it)->users.end())
            (*it)->users.erase(std::find((*it)->users.begin(), (*it)->users.end(), &(server.client[readfds[index].fd])));
        if (std::find((*it)->op.begin(), (*it)->op.end(), &(server.client[readfds[index].fd])) != (*it)->op.end())
            (*it)->op.erase(std::find((*it)->op.begin(), (*it)->op.end(), &(server.client[readfds[index].fd])));
    }
    close(readfds[index].fd);
    server.client.erase(readfds[index].fd);
    readfds.erase(find_pollfd(readfds, readfds[index]));
}

int main(int argc, char *argv[])
{
    Client client;
    std::vector<pollfd> readfds(1);
    int                 new_size;
    Server              server;
    
    if (argc == 3 && argv[2][0] != ' ')
    {
        try{
        if (argv_is_digit(argv[1]) == 0)
        {
            perror("Port must be a digit\n");
            return (0);
        }
        server.serversocket = server.create_socket();
        if ((client.addrlen = server.bind_socket_to_port(argv[1], server.serversocket)) < 0)
            return (1);
        readfds[0].fd = server.serversocket;
        readfds[0].events = POLLIN;
        while (1)
        {
            int activity;
            activity = poll(readfds.data(), readfds.size(), -1);
            if ((activity < 0))
                perror("Error occured in poll\n");
            new_size = readfds.size();
           for (int index = 0; index < new_size; index++)
           {
                if (readfds[index].revents == 0)
                    continue;
                if (readfds[index].revents != POLLIN)
                {
                    clear_client(index, server, readfds);
                    break;
                }
                if (readfds[index].fd == server.serversocket)
                    readfds = client.connection_multi_client_srv(server.serversocket, readfds, server);
                else
                    server.client[readfds[index].fd].send_recv_msg(readfds, argv[2], &index, server);
           }
        }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
	else
	{
		perror("This is the correct use: ./ircserv <port> <password> \nPassword should not start with a space!\n");
		return (1);
	}
    for (int index = 0; index < (int)readfds.size(); index++)
        close(readfds[index].fd);
    close(server.serversocket);
    return (0);
}
