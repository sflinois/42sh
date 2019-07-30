# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/01 20:40:22 by rkhalfao          #+#    #+#              #
#    Updated: 2019/03/15 17:54:30 by rkhalfao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src/

SRC_NAME = ft_atoi.c \
	   ft_bzero.c \
	   ft_isalnum.c\
	   ft_isalpha.c \
	   ft_isascii.c\
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_memalloc.c \
	   ft_memccpy.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memdel.c \
	   ft_memmove.c \
	   ft_memset.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strclr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdup.c \
	   ft_strequ.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strncpy.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strstr.c \
	   ft_strsub.c \
	   ft_strtrim.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_strdel.c \
	   ft_putchar.c \
	   ft_putstr.c \
	   ft_putnbr.c \
	   ft_putendl.c \
	   ft_putstr_fd.c \
	   ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_strsplit.c \
	   ft_itoa.c \
	   ft_lstnew.c \
	   ft_lstdelone.c \
	   ft_lstdel.c \
	   ft_lstadd.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_strndup.c \
	   ft_create_tab.c \
	   ft_print_map.c \
	   ft_strclen.c \
	   ft_strjoinfree.c \
	   ft_strcdup.c \
	   get_next_line.c \
	   ft_check_if_int.c \
	   check_full_space.c \
	   ft_strchrstr.c \
	   ft_strsplit_miss.c \
	   ft_strexplode.c \
	   ft_free_tab.c \
	   ft_create_first_step_tab.c \
	   ft_close_load_directory.c \
	   ft_check_right_exec.c \
	   ft_unsplit_tab.c \
	   ft_strjoinmiddle.c \
	   ft_find_char_in_str.c \
	   ft_go_to_the_next_same_char.c \
	   echap_charac.c \
	   delete_space_local.c \
	   protect_atoi.c \
	   next_char_without_space.c \
	   if_alpha_or_digit.c \
	   nb_arg_tab.c \
	   ft_printf.c \
	   ft_tc_my_outc.c \
	   ft_tc_clear_all_after_cursor.c \
	   ft_tc_down_cursor.c \
	   ft_tc_save_cursor.c \
	   ft_tc_restaure_cursor.c \
	   ft_tc_move_cursor_one_right.c \
	   ft_tc_move_cursor_one_left.c \
	   ft_tc_up_cursor_one_line.c \
	   ft_tc_select_mode.c \
	   ft_tc_end_select_mode.c \
	   ft_tc_del_character.c \
	   ft_tc_clean_screen.c \
	   ft_tc_clean_line_aft_cursor.c \
	   before_flags_on_int.c \
	   big_c_arg.c \
	   big_dou_arg.c \
	   check_before_conv.c \
	   fill_buffer.c \
	   flag_on_int2.c \
	   flag_on_str.c \
	   flags_on_int.c \
	   ft_itoa_base.c \
	   s_arg_def_size.c \
	   start_int_func_diez.c \
	   tools.c \
	   ws_arg.c

OBJS = $(SRC_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) -rcs $(NAME) $?
	@echo "\033[32m$(NAME) created successfully\033[0m"

%.o: srcs/%.c
	@$(CC) -c -o $@ $< -I includes/ $(CFLAGS)

# %.o: srcs_ft_printf/%.c 
# 	@$(CC) -c -o $@ $< -I includes/ $(CFLAGS)

# %.o: srcs_termcaps/%.c 
# 	@$(CC) -c -o $@ $< -I includes/ $(CFLAGS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all