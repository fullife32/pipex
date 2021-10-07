# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 14:20:42 by eassouli          #+#    #+#              #
#    Updated: 2021/10/07 18:50:21 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

MKDIR	=	/bin/mkdir -p

CC	=	/usr/bin/clang

MAKE	=	/usr/bin/make -C

RM	=	/bin/rm -rf

INCLUDE	=	-I includes/.

PATH_S	=	srcs/

PATH_B	=	build/

SRCS	+=	main/pipex.c

SRCS	+=	init/init_check.c

SRCS	+=	create_list/create_list.c \
			create_list/split_elements.c

SRCS	+=	fork/start_fork.c \
			fork/exec_cmd.c \
			fork/in_and_out.c

SRCS	+=	free_and_return/free_pipex.c \
			free_and_return/return_value.c

SRCS	+=	utils/ft_lstclear.c \
			utils/ft_lstdelone.c \
			utils/ft_lstnew.c \
			utils/ft_split.c \
			utils/ft_strdup.c \
			utils/ft_strjoin.c \
			utils/ft_strlen.c \
			utils/ft_strncmp.c \

OBJS	=	$(addprefix $(PATH_B), $(SRCS:.c=.o))

CFLAGS	=	-g -Wall -Wextra -Werror $(INCLUDE)

all:	$(PATH_B) $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(PATH_B):
	$(MKDIR) $(PATH_B) $(PATH_B)/main $(PATH_B)/init $(PATH_B)/create_list $(PATH_B)/fork $(PATH_B)/utils $(PATH_B)/free_and_return/

$(PATH_B)%.o:	$(PATH_S)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(PATH_B)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re