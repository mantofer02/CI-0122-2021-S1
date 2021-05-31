NODE_A = node_a 
NODE_B = node_b
EXECUTABLES=$(NODE_A) $(NODE_B)

CC = g++
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = -pthread

all: $(EXECUTABLES)

$(NODE_A): node.cpp 
	$(CC) $(CFLAGS) node.cpp -o $(NODE_A)

$(NODE_B): node.cpp 
	$(CC) $(CFLAGS) node.cpp -o $(NODE_B)


.PHONY: build
build: $(EXECUTABLES)

.PHONY: rebuild
rebuild: clean $(EXECUTABLES)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting node.cpp 

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)