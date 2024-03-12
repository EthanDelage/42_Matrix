NAME		=		matrix_test

#######################
#	DIR
#######################

SRC_DIR		=		./

INC_DIR		=		./

BUILD_DIR	=		.build/

#######################
#	FILES
#######################

SRC			=		main.cc			\
					tests/code_constraints.cc	\
					tests/ex00.cc	\
					tests/ex01.cc	\

OBJ			=		$(addprefix $(BUILD_DIR), $(SRC:.cc=.o))

DEPS		=		$(OBJ:.o=.d)

#######################
#	FLAGS
#######################

CFLAGS		=		-Wall -Werror -Wextra -std=c++20

IFLAGS		=		-I $(INC_DIR)

DFLAGS		=		-MMD -MP

#######################
#	RULES
#######################

############
#	GENERAL
############

.PHONY:				all
all:				$(NAME)

.PHONY:				clean
clean:
					$(RM) $(OBJ) $(DEPS)

.PHONY:				fclean
fclean:
					$(RM) $(OBJ) $(DEPS) $(NAME)

.PHONY:				re
re:					fclean
					$(MAKE)

.PHONY:				run
run:				all
					./$(NAME)

################
#	EXECUTABLES
################

-include			$(DEPS)

$(NAME):			$(OBJ)
					$(CXX) $(CFLAGS) $(IFLAGS) $^ -o $@

##################
#	OBJECTS FILES
##################

$(BUILD_DIR)%.o:	$(SRC_DIR)%.cc
					mkdir -p $(shell dirname $@)
					$(CXX) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@