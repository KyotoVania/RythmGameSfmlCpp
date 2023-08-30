##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-raytracer-jalel.belkacem
## File description:
## Makefile
##

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -Iinclude -g3 -fopenmp -pthread
ASAN_FLAGS = -O1 -g -fsanitize=address -fno-omit-frame-pointer
#need to add sfml-graphics
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lconfig++
# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = .

# Files
SRCS = $(wildcard $(SRCDIR)/**/*.cpp $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
EXEC = $(BINDIR)/YinYang
# Targets
all: $(EXEC)
	@echo "$(GREEN)Compilation successful!$(NC)"

$(EXEC): $(OBJS)
	@echo "$(YELLOW)Linking...$(NC)"
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ && \
	echo "$(GREEN)Compiled $< successfully!$(NC)" || \
	(echo "$(RED)Failed to compile $<!$(NC)" && false)

debug: CFLAGS += $(ASAN_FLAGS)
debug: all

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@rm -f $(EXEC)

re: fclean all

fclean: clean
	@echo "$(RED)Removing object files...$(NC)"
	@rm -rf $(OBJDIR)

check:
	@echo "Source files:" $(SRCS)
	@echo "Object files:" $(OBJS)

distcheck: check
	@echo "Source directory:" $(SRCDIR)
	@echo "Object directory:" $(OBJDIR)
	@echo "Binary directory:" $(BINDIR)
	@echo "Binary name:" $(EXEC)

.PHONY: all clean debug re fclean check distcheck