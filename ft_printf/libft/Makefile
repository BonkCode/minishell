# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/06 19:31:02 by rtrant            #+#    #+#              #
#    Updated: 2020/05/13 18:30:36 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
RM = rm -f 
SRCS =  ft_atoi.c ft_bzero.c ft_isalpha.c ft_isascii.c \
        ft_isdigit.c ft_isprint.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
        ft_memset.c ft_strlcpy.c ft_strlen.c ft_tolower.c ft_toupper.c \
        ft_strnstr.c ft_isalnum.c ft_memccpy.c ft_strrchr.c ft_strchr.c \
        ft_memchr.c ft_calloc.c ft_strdup.c ft_strncmp.c ft_strlcat.c \
        ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
        ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
        
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
            ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
                
OBJS =  ft_atoi.o ft_bzero.o ft_isalpha.o ft_isascii.o \
        ft_isdigit.o ft_isprint.o ft_memcmp.o ft_memcpy.o ft_memmove.o \
        ft_memset.o ft_strlcpy.o ft_strlen.o ft_tolower.o ft_toupper.o \
        ft_strnstr.o ft_isalnum.o ft_memccpy.o ft_strrchr.o ft_strchr.o \
        ft_memchr.o ft_calloc.o ft_strdup.o ft_strncmp.o ft_strlcat.o \
        ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o \
        ft_strmapi.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o

BONUS_OBJS = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o \
            ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

BLACK        := $(shell tput -Txterm setaf 0)
RED          := $(shell tput -Txterm setaf 1)
GREEN        := $(shell tput -Txterm setaf 2)
YELLOW       := $(shell tput -Txterm setaf 3)
LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
PURPLE       := $(shell tput -Txterm setaf 5)
BLUE         := $(shell tput -Txterm setaf 6)
WHITE        := $(shell tput -Txterm setaf 7)

RESET := $(shell tput -Txterm sgr0)

all: $(NAME)

$(OBJS):
	@gcc -Wall -Wextra -Werror -c $(SRCS)
	@echo "${GREEN}Compiled source files${RESET}"

$(BONUS_OBJS):
	@gcc -Wall -Wextra -Werror -c $(BONUS_SRCS)
	@echo "${GREEN}Compiled bonus source files${RESET}"

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "${GREEN}Compiled object files${RESET}"

bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)
	@echo "${GREEN}Compiled bonus object files${RESET}"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "${BLUE}Removed all object files${RESET}"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft.so
	@echo "${BLUE}Removed library file${RESET}"

re: fclean all

.PHONY: all clean fclean re bonus