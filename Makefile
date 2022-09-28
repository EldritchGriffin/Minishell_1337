# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 04:58:41 by zrabhi            #+#    #+#              #
#    Updated: 2022/09/28 04:18:15 by aelyakou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(GREEN)$(shell basename $<)$(GREEN

##############################colors####################################################################
RED    := \033[0;31m
WHITE  := \033[0;37m
GREEN  := \033[0;32m
BLUE   := \033[0;34m
YELLOW := \033[0;33m
########################################################################################################
draw       := draw
HEADER_DIR := headers
LIBFT_DIR  := LIBFT
GNL_DIR    := gnl
FILE	   := files
LIBFT      := $(LIBFT_DIR)/libft.a
GNL 	   := $(GNL_DIR)/get_next_line.a
SRC_DIR    := src
OBJ_DIR    := obj
TOOLS      := cmd_list exc_list
ENV        := env_list
EXEC       := built_ins env_sort exec_utils execve ft_cd ft_echo ft_export ft_pwd ft_unset pipe_exe
PARSING    := final_check parser_utils  parser parser2 parser3  free_list syntax_errors tokenizer_utils tokenizer_utils2 tokenizer var_expander here_doc execlist_builder flag_str
src        := ft_shell
SRC        := $(addsuffix .c, $(addprefix src/env/, $(ENV))) \
	  					$(addsuffix .c, $(addprefix src/execution/, $(EXEC))) \
	  							$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
	 									$(addsuffix .c, $(addprefix src/tools/, $(TOOLS))) \
										 	$(addsuffix .c, $(addprefix src/, $(src))) \

main        := 	$(SRC_DIR)/main/main.c
OBJ	        := $(SRC:.c=.o)
CC          := 	gcc
GCCFLAGS    := -Wall -Wextra -Werror -lreadline  -g #-static-libsan -fsanitize=address
HEADER      := $(HEADER_DIR)/minishell.h
NAME        := Minishell
RECOMPILING := echo "     $(YELLOW)Recompiling..........$(YELLOW)"

###################################TARGETS##############################################################

all : $(NAME)
	@echo""
	@echo " $(YELLOW)Welcome to$(YELLOW) "
	@echo "$(RED)"
	@cat $(draw)/minishell-art.ans
	@echo""
	@echo "                				$(YELLOW)By zrabhi && aelyakou $(YELLOW)                        "

$(NAME) : create_dir  $(OBJ) $(main) $(HEADER) $(LIBFT) $(GNL)
	@echo "\n"
	@echo " $(YELLOW)Source files are compiled!\n$(YELLOW)"
	@echo  "Building $(NAME) for" "Mandatory" "..."
	@$(CC) $(GCCFLAGS) $(main) $(LIBFT) $(GNL) $(OBJ) -o $(NAME)
	@echo""
	@sleep 0.1.5
	@sleep 0.2
	@echo ""
	@echo  "$(NAME) is created!\n"

################# wild card used in this make file , im gonna change it later#########################################
# create_dir:
# 	@mkdir -p $(OBJ_DIR)
$(GNL)   :
	@$(MAKE) -C $(GNL_DIR)
$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

######################################################################################################################

%.o: %.c
	@echo "$(YELLOW)creating : $(@:OBJ/%=%) "
	@sleep 0.05
	@$(CC) $(GCCFLAG) -g -c $< -o $@

#####################################################REMOVING ABJECTS FILE####################################
create_dir :
	@mkdir -p $(FILE)
clean :
	@echo "$(YELLOW)Removing Objects file ....    $(GREEN)$(shell basename $(OBJ))$(GREEN)"
	@rm -rf $(OBJ)
	@echo "     $(YELLOW)Successfully Removed$(YELLOW)"

##############################REMOVING OBJECTS FILE AND EXE###################################################

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR)/ fclean
	@$(MAKE) -C $(GNL_DIR)/ fclean
	@echo "$(YELLOW)Removing Minishell ....    $(GREEN)$(shell basename $(NAME))$(GREEN)"
	@rm -rf $(NAME)
	@echo "     $(YELLOW)Successfully Removed$(YELLO)"

#################################################RECOMPILING####################################################

re: fclean all
	@echo "     $(YELLOW)Recompiling..........$(YELLOW)"
