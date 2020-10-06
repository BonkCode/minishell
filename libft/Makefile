# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 16:30:05 by rtrant            #+#    #+#              #
#    Updated: 2020/10/06 12:53:54 by rvernius         ###   ########.fr        #
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
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c get_next_line_utils.c \
		ft_add_hex_rep.c ft_i_add_sign.c \
		ft_get_char_print.c \
		ft_get_int_print.c ft_get_pointer_print.c \
		ft_get_string_print.c ft_get_unsigned_int_print.c \
		ft_printfutils.c ft_directive.c \
		ft_get_conversion_character.c ft_get_field_width.c ft_get_flags.c \
		ft_get_length_modifier.c ft_get_precision.c ft_printf.c \
		ft_print_variants.c
		
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				
OBJS =	$(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(OBJS):
	@gcc -Wall -Wextra -Werror -c $(SRCS)

$(BONUS_OBJS):
	@gcc -Wall -Wextra -Werror -c $(BONUS_SRCS)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus: $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft.so

re: fclean all

.PHONY:	all clean fclean re bonus