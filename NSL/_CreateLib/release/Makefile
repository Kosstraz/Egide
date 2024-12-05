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

NAME = libnsl.a

CXX =	@c++

AR =	@ar -rcs

SRCS =	./env/NSLSIMDplatform.cpp						\
		./env/NSLsrcs/private/Async.cpp					\
		./env/NSLsrcs/private/Barrier.cpp				\
		./env/NSLsrcs/private/Channel.cpp				\
		./env/NSLsrcs/private/IOStream.cpp				\
		./env/NSLsrcs/private/ManagedBarrier.cpp		\
		./env/NSLsrcs/private/MultiThreading.cpp		\
		./env/NSLsrcs/private/Mutex.cpp					\
		./env/NSLsrcs/private/MutexRecursive.cpp		\
		./env/NSLsrcs/private/MutexStrict.cpp			\
		./env/NSLsrcs/private/Pool.cpp					\
		./env/NSLsrcs/private/Signal.cpp				\
		./env/NSLsrcs/private/Sleep.cpp					\
		./env/NSLsrcs/private/String.cpp				\
		./env/NSLsrcs/private/Thread.cpp				\
		./env/NSLsrcs/private/ThreadQueue.cpp			\
		./env/NSLsrcs/private/Vector3d_op.cpp			\
		./env/NSLsrcs/private/Vector3d.cpp				\
		./env/NSLsrcs/private/Vector3f_op.cpp			\
		./env/NSLsrcs/private/Vector3f.cpp				

LMAKE = @make --no-print-directory -C

OBJS_DIR = objs

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I ./env/srcs -I .

CFLAGS = -std=c++20 -Wall -Wextra -Winline -Wno-comment -Wno-unknown-pragmas -MMD -O3 -march=native -g3

LIB = -lpthread

# ############## #
#*    REGLES    *#
# ############## #

all: YAY $(NAME)

$(NAME): $(OBJS)
	$(AR)  $(NAME) $(OBJS) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

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
