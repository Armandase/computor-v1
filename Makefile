MAKEFLAGS += -j

CXX		=	c++
NAME 	= 	computor
SRC 	=	main.cpp parsing.cpp \
			Monom.cpp Polynom.cpp \
			parsing_utils.cpp utils.cpp

HEADER	=	inc/parsing.h inc/parsing_utils.h \
			inc/Monom.h inc/Polynom.h \
			inc/matplotlibcpp.h inc/utils.h

OBJS	=	$(addprefix obj/, $(SRC:.cpp=.o))
CXXFLAGS=	-Wall -Wextra -Werror --std=c++17 -g \
			-DPLOT -DWITHOUT_NUMPY -DACTIVATE_PLOT=0
LDFLAGS	=	-lpython3.10

all		:	${NAME} 

${NAME}	:	${OBJS} ${HEADER}
			${CXX} -o ${NAME} ${OBJS} ${LDFLAGS}

lib		:	
			pip install matplotlib

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf obj/

re: fclean
	@make all

.PHONY: all fclean clean re lib
