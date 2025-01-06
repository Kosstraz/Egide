# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
WHITE	= \e[38;2;238;232;213m
BOLD	= \e[1m
# BLACK	= \e[38;2;0;0;0m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[38;2;0;36;148m
PURPLE 	= \e[38;2;211;54;130m
CYAN   	= \e[36m
YELLOW 	= \e[38;2;250;189;0m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = egide_tester
LNAME = libegide.a

CXX = @c++
AR = @ar -rcs

ALL_SRCS =	./egide/egide_SIMDplatform.cpp			\
			./egide/src/private/String.cpp			\
			./egide/src/private/IOStream.cpp		\
			./egide/src/private/Pool.cpp			\
			./egide/src/private/Sleep.cpp			\
			./egide/src/private/Mutex.cpp			\
			./egide/src/private/MutexStrict.cpp		\
			./egide/src/private/MutexRecursive.cpp	\
			./egide/src/private/Barrier.cpp			\
			./egide/src/private/ManagedBarrier.cpp	\
			./egide/src/private/Async.cpp			\
			./egide/src/private/Thread.cpp			\
			./egide/src/private/ThreadQueue.cpp		\
			./egide/src/private/Channel.cpp			\
			./egide/src/private/MultiThreading.cpp	\
			./egide/src/private/Vector3d.cpp		\
			./egide/src/private/Vector3d_op.cpp		\
			./egide/src/private/Vector3f.cpp		\
			./egide/src/private/Vector3f_op.cpp		\
			./egide/src/private/Signal.cpp			\

SRCS =	$(ALL_SRCS)	\
		./main.cpp

LSRCS =	$(ALL_SRCS)

LMAKE = @make --no-print-directory -C

OBJS_DIR = objs

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.obj)
LOBJS = $(LSRCS:%.cpp=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I ./env/srcs -I .

CFLAGS = -std=c++20 -Wall -Wextra -Winline -Wno-comment -Wno-unknown-pragmas -MMD -O3 -march=native -g3
#-Wno-non-template-friend 
#-Wno-unsupported-friend

LIB = -lpthread

# ############## #
#*    REGLES    *#
# ############## #

all: YAY $(NAME)

lib: YAY $(LNAME)

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIB) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

$(LNAME): $(LOBJS)
	$(AR) $(LNAME) $(LOBJS)
	@echo "$(BOLD)$(CYAN)Librairie $(NAME) créé avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.obj: %.cpp
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CXX) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)"
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	@echo "$(BOLD)$(RED)"
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)

# ############## #
#*    AUTRES    *#
# ############## #

YAY:
	@echo "$(PURPLE)$(BOLD)Compilation avec les flags suivants : "
	@echo $(CFLAGS)
	@echo "$(CLASSIC)"
