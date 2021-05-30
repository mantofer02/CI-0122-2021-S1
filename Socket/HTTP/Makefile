SERVER = server
CLIENT = client
EXECUTABLES=$(SERVER) $(CLIENT)

CC = g++
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = -pthread

all: $(EXECUTABLES)

$(SERVER): $(SERVER).cpp 
	$(CC) $(CFLAGS) $(SERVER).cpp -o $(SERVER)

$(CLIENT): $(CLIENT).cpp 
	$(CC) $(CFLAGS) $(CLIENT).cpp -o $(CLIENT)


.PHONY: build
build: $(EXECUTABLES)

.PHONY: rebuild
rebuild: clean $(EXECUTABLES)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(SERVER).cpp $(CLIENT).cpp 

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)