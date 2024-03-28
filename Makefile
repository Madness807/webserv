NAME			=		webserv

# Ajout du dessin ASCII comme une variable
LOGO = "\
 _    _      _                         \n\
| |  | |    | |                        \n\
| |  | | ___| |__  ___  ___ _ ____   __\n\
| |/\| |/ _ \\ '_ \\/ __|/ _ \\ '__\\ \\ / /\n\
\  /\  /  __/ |_) \\__ \\  __/ |   \\ V / \n\
 \/  \/ \\___|_.__/|___/\\___|_|    \\_/  \n\
                                        \n\
"

# Sources / Objs
SRC				=		main.cpp\
						src/ConfigParser/ConfigParser.cpp\
						src/ConfigParser/ServerConfig.cpp\
						src/ConfigParser/LocationConfig.cpp\
						src/Server/Server.cpp\
						src/Client/Client.cpp\
						src/Response/Response.cpp\
						src/Request/Request.cpp\
						src/Request/delete.cpp\
						src/Request/get.cpp\
						src/Request/post.cpp\
						src/Request/Parse.cpp\
						src/Connection/Connection.cpp\
						src/CGIHandler/CGIHandler.cpp\
						src/verbose/verbose.cpp\

OBJ_DIR			=		build/
OBJ			=		$(patsubst src/%,$(OBJ_DIR)%,$(SRC:.cpp=.o))

# Compiler and flags
CXX				=		g++
CXXFLAGS		=		-Wall -Wextra -Werror -std=c++98 -g

# Recipes
all: logo start $(NAME)

# Afficher le logo
logo:
	@echo $(LOGO)

start:
	@echo "Compilation started..."

$(OBJ_DIR)%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -I include -c $< -o $@


$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation of $(NAME) finished."

clean:
	@rm -f $(OBJ)
	@echo "Cleaned up object files."

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned up compiled binary."

re: fclean all

.PHONY: all clean fclean re
