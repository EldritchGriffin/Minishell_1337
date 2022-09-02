# $(GREEN)$(shell basename $<)$(GREEN

##############################colors####################################################################
RED   := \033[0;31m
WHITE := \033[0;37m
GREEN := \033[0;32m
BLUE  := \033[0;34m
YELLOW := \033[0;33m
########################################################################################################

####
###########################TODO: createe objects Directorie######################
####
######################################Directories#######################################################

draw = draw
HEADER_DIR = headers
LIBFT_DIR = LIBFT
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
PARSING = $(SRC_DIR)/parsing
TOOLS = $(SRC_DIR)/tools
ENV = $(SRC_DIR)/env
EXEC = $(SRC_DIR)/execution
PARSING_DIR = $(SRC_DIR)/parsing

SRC = 	$(SRC_DIR)/ft_shell.c $(PARSING)/parser_utilis.c $(PARSING)/tokenizer.c $(PARSING)/parser.c $(TOOLS)/cmd_lst.c $(PARSING)/tokenizer_utilis.c $(PARSING)/tokenizer_utilis2.c $(PARSING)/syntax_errors.c $(ENV)/env_list.c $(EXEC)/env_sort.c $(EXEC)/built_ins.c
main = 	$(SRC_DIR)/main.c
OBJ	= 	$(SRC:.c=.o)
CC = 	gcc
GCCFLAGS = -Wall -Wextra -Werror -lreadline  -g -static-libsan -fsanitize=address
         	#-I $(shell brew --prefix readline)/include \
     		#-L $(shell brew --prefix readline)/lib -lreadline \
        	#-L $(shell brew --prefix readline)/lib -lhistory -g

###################################This flag includes readline && history library##########################

# GCCFLAG = -Wall -Wextra -Werror \
        	-I $(shell brew --prefix readline)/include

HEADER   = $(HEADER_DIR)/minishell.h
NAME     = Minishell
RECOMPILING = echo "     $(YELLOW)Recompiling..........$(YELLOW)"

###################################TARGETS##############################################################

all : $(NAME)
	@echo""
	@echo " $(YELLOW)Welcome to$(YELLOW) "
	@echo "$(RED)"
	@cat $(draw)/minishell-art.ans
	@echo""
	@echo "                				$(YELLOW)By zrabhi && aelyakou $(YELLOW)                        "

$(NAME) : $(OBJ) $(main) $(HEADER) $(LIBFT)
	@echo "\n"
	@echo " $(YELLOW)Source files are compiled!\n$(YELLOW)"
	@echo  "Building $(NAME) for" "Mandatory" "..."
	@$(CC) $(GCCFLAGS) $(main) $(LIBFT) $(OBJ) -o $(NAME)
	@echo""
	@sleep 0.2
	@sleep 0.2
	@echo ""
	@echo  "$(NAME) is created!\n"

################# wild card used in this make file , im gonna change it later#########################################

$(LIBFT) : $(shell find $(LIBFT_DIR) -name "*.c" -type f)
	@$(MAKE) -C $(LIBFT_DIR)

######################################################################################################################

%.o: %.c	
	@echo "$(YELLOW)creating : $(@:OBJ/%=%) "
	@sleep 0.2
	@$(CC) $(GCCFLAG) -g -c $< -o $@   

#####################################################REMOVING ABJECTS FILE####################################

clean :
	@echo "$(YELLOW)Removing Objects file ....    $(GREEN)$(shell basename $(OBJ))$(GREEN)"
	@rm -rf $(OBJ)
	@echo "     $(YELLOW)Successfully Removed$(YELLOW)"

##############################REMOVING OBJECTS FILE AND EXE###################################################

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR)/ fclean
	@echo "$(YELLOW)Removing Minishell ....    $(GREEN)$(shell basename $(NAME))$(GREEN)"
	@rm -rf $(NAME)
	@echo "     $(YELLOW)Successfully Removed$(YELLO)"

#################################################RECOMPILING####################################################

re: fclean all
	@echo "     $(YELLOW)Recompiling..........$(YELLOW)"
