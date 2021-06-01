APPNAME=endpoint
EXECUTABLES=$(APPNAME)

CC = g++
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = -pthread

all: $(EXECUTABLES)

$(APPNAME): main.cpp $(APPNAME).cpp 
	$(CC) $(CFLAGS) main.cpp $(APPNAME).cpp -o $(APPNAME)


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