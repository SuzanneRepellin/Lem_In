# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/19 13:05:59 by srepelli     #+#   ##    ##    #+#        #
#    Updated: 2018/08/31 13:18:18 by srepelli    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lem-in

SRCS = read_stde_map.c \
	   read_stde_tubes.c \
	   t_room_tools.c \
	   lem_in.c \
	   display.c \
	   parse.c \
	   t_tube_tools.c \
	   path_tools.c \
	   find_shortest_path.c \
	   com_tools.c

SRCPATH = src/

OBJPATH = obj/

OBJ = $(addprefix $(OBJPATH),$(SRCS:.c=.o))

HEAD = -I includes/

FLAGS = -Wall -Wextra -Werror -g

LIBPATH = libft/

LIB = libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc $(FLAGS) $(HEAD) $(LIBPATH)$(LIB) $(OBJ) -o $(NAME)

$(LIB):
	$(MAKE) -C $(LIBPATH)

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(OBJPATH)%.o: $(SRCPATH)%.c | $(OBJPATH)
	gcc $(FLAGS) $(HEAD) -c $< -o $@

clean:
	/bin/rm -rf $(OBJPATH)
	$(MAKE) fclean -C $(LIBPATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
