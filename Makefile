# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/15 11:20:37 by rkhalfao          #+#    #+#              #
#    Updated: 2019/04/02 19:45:22 by rkhalfao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBDIR = libft/
LIBNAME  = libft/libft.a
LIBFLAGS = -Llibft -lft -ltermcap

INC= -I./includes/ -I./libft/includes/

SRC_PATH = srcs/

VPATH  = .: srcs/ast srcs/lexer srcs/job_control srcs/line_editor \
		srcs/redirections srcs/hashtable srcs/builtins \
		srcs/builtins/builtins_env srcs/line_editor/key_interpretor \
		srcs/parser srcs/error srcs/create_base_project \
		srcs/lexer/lex_dollar srcs/

SRC_NAME = main.c \
			do_func.c \
			exec_with_abs_path.c \
			exec_ast_node.c \
			DELETE_BEFORE_PUSH.c \
			\
			create_list_stock_line_histo.c \
			replace_backslashn.c \
			find_recup_history.c \
			replace_histo_in_buff.c \
			edit_histo_file_exit.c \
			upload_file_histo_in_list.c \
			go_read.c \
			modif_keyboard_shell.c \
			move_cursor_to_the_end.c \
			move_cursor_to_the_start.c \
			print_character.c \
			print_prompt.c \
			rewrite_buf_copy_mode.c \
			\
			receive_buffer_tokenize.c \
			if_space.c \
			lex_and.c \
			lex_inhibitor.c \
			lex_redir_right.c \
			lex_redir_left.c \
			lex_redir_global.c \
			join_chain_redir.c \
			lex_others.c \
			create_list_tkn.c \
			\
			inser_on_buffer.c \
			del_on_buff.c \
			transforme_expansion.c \
			lex_dollar_diez_first.c \
			verif_if_param_exist.c \
			simple_dollar.c \
			dollar_union.c \
			dollar_equal.c \
			dollar_query.c \
			dollar_add.c \
			dollar_percent_diez.c \
			tilde.c \
			\
			ast_creation.c \
			ast_browsing.c \
			\
			redir_exec.c \
			input_redir.c \
			output_redir.c \
			pipe_redir.c \
			redir_utils.c \
			redir_utils2.c \
			lst_fd_utils.c \
			\
			hashtable.c\
			builtin_hash.c\
			builtin_hash_pars.c\
			\
			builtin_fg.c \
			builtin_bg.c \
			builtin_jobs.c \
			handle_jobs.c \
			get_job_name.c \
			handle_statuses.c \
			\
			if_builtin.c \
			builtin_cd_path_oldenv.c \
			builtin_cd_home_old.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_exit.c \
			builtin_setenv.c \
			builtin_set.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_unsetenv.c \
			builtin_history.c \
			builtin_alias.c \
			builtin_alias_pars.c \
			builtin_unalias.c \
			env_or_set.c \
			\
			touch_clean_screen.c \
			touch_ctrl_r.c \
			touch_ctrl_r_inser.c \
			touch_opt_and_arrow.c \
			touch_copy_and_paste.c \
			touch_del.c \
			touch_home_and_end.c \
			touch_left_right_arrow.c \
			touch_opt_down.c \
			touch_opt_up.c \
			touch_shift_and_arrow.c \
			touch_top_and_down_arrow.c \
			touch_tab.c \
			touch_tab_define_arg_to_comp.c \
			touch_tab_stock_arg_in_list.c \
			touch_tab_func_create_list.c \
			touch_tab_print_list.c \
			touch_tab_possibility_comp.c \
			touch_tab_color.c \
			get_position_cursor.c \
			\
			builtin_env.c \
			modify_copy_list_env.c \
			modify_tab_env.c \
			recup_options.c \
			process_options.c \
			print_list.c \
			\
			touch_entry.c \
			go_to_parse_dollar_pipe_and.c \
			parse_pipe_and.c \
			parse_dollar.c \
			parse_dollar_posibility_expansion.c \
			parse_inhib.c \
			parse_heredoc.c \
			parse_redir.c \
			parse_semico.c \
			get_arg_heredoc.c \
			get_arg_heredoc_del_buf.c \
			create_list_heredoc.c \
			\
			print_error_for_exit.c \
			print_error_other.c \
			print_error_set_unset.c \
			print_error_env.c \
			print_error_substitution.c \
			print_error_exclam.c \
			print_error_alias.c \
			\
			add_required_env.c \
			replace_alias.c \
			create_tab_path_and_list_env.c \
			genere_struct_shell.c \
			func_free.c \
			recup_tab_argv.c \
			tools_src.c


OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make all -C libft
	@$(CC) $(LIBFLAGS) $(INC) -o $@ $^ -g
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
	@make -C libft/ clean
	@echo Clean success

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo Fclean success

re: fclean $(NAME)

.PHONY: all clean fclean re
