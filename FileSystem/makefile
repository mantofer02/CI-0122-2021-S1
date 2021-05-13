APPNAME = filesystem
SRCFOLDER = src/
BINFOLDER = bin/
HEADERS = headers/
EXECUTABLES = $(APPNAME) 
#$(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan $(APPNAME)_ubsan

CC = g++
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = 

all: $(EXECUTABLES)

$(APPNAME): $(SRCFOLDER)*.cpp
	g++ $(CFLAGS) $(SRCFOLDER)*.cpp -I $(HEADERS) -o $(BINFOLDER)$(APPNAME) $(LIBS)

#$(APPNAME)_asan: $(SRCFOLDER)*.cpp
#	$(CC2) $(CFLAGS) -fsanitize=address $(SRCFOLDER)*.cpp -o $(BINFOLDER)$(APPNAME)_asan $(LIBS)

#$(APPNAME)_msan: $(SRCFOLDER)*.cpp
#	$(CC2) $(CFLAGS) -fsanitize=memory $(SRCFOLDER)*.cpp -o $(BINFOLDER)$(APPNAME)_msan $(LIBS)

#$(APPNAME)_tsan: $(SRCFOLDER)*.cpp
#	$(CC2) $(CFLAGS) -fsanitize=thread $(SRCFOLDER)*.cpp -o $(BINFOLDER)$(APPNAME)_tsan $(LIBS)

#$(APPNAME)_ubsan: $(SRCFOLDER)*.cpp
#	$(CC2) $(CFLAGS) -fsanitize=undefined $(SRCFOLDER)*.cpp -o $(BINFOLDER)$(APPNAME)_ubsan $(LIBS)

.PHONY: memcheck
memcheck:
	valgrind ./$(BINFOLDER)$(APPNAME)

.PHONY: memcheck_full
memcheck_full:
	valgrind --leak-check=full ./$(BINFOLDER)$(APPNAME)

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind ./$(BINFOLDER)$(APPNAME)

.PHONY: rebuild
rebuild: clean $(EXECUTABLES)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(SRCFOLDER)*.cpp

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(BINFOLDER)$(EXECUTABLES)