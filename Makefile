# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 15:12:06 by zel-hach          #+#    #+#              #
#    Updated: 2023/08/09 21:27:27 by ssadiki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = server.cpp client.cpp User.cpp commands.cpp join_cmd.cpp kick_cmd.cpp invite_cmd.cpp main.cpp \
	Channel.cpp cmd_topic.cpp cmd_mode.cpp privs_msg.cpp cmd_to_connection.cpp \
 	affiche_reply_mode.cpp add_remove_mode.cpp utils.cpp notice.cpp bot_cmd.cpp
INCLUDE = server.hpp client.hpp User.hpp commands.hpp Channel.hpp replies.hpp
OBJECTS = $(SRC:.cpp=.o)

all: $(NAME)

ircserv :	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf $(OBJECTS)
fclean:clean
	rm -rf $(NAME)

re: fclean all
