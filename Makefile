NAME		=		matrix_test

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		src/

BUILD_DIR	=		.build/

#######################
#	FILES
#######################

SRC			=		main.cc			\
					tests/code_constraints.cc	\
					tests/basic_arithmetic.cc	\
					tests/linear_combination.cc	\
					tests/linear_interpolation.cc	\
					tests/dot_product.cc	\
					tests/norm.cc	\
					tests/angle_cos.cc	\
					tests/cross_product.cc	\
					tests/linear_map.cc	\
					tests/matrix_multiplication.cc	\
					tests/trace.cc

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