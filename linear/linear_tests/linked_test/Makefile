##########################################
#           Editable options             #
##########################################

# Compiler options
CC=g++
CFLAGS=-c -Wall -I../../linked_list/inc
LDFLAGS=-L../../linked_list/lib -llinked_list

EXECUTABLE_NAME=test_linked_list

# Folders
SRC=src
BIN=bin
OBJ=./obj
 
# Files
C_FILES   = $(wildcard src/*.c)
CPP_FILES = $(wildcard src/*.cpp)

#########################################################
# Replacing everything that you told me not to touch... #
#########################################################
EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(C_FILES:%.c=$(OBJ)/%.o)
CPP_OBJECT_FILES = $(CPP_FILES:%.cpp=$(OBJ)/%.o)
# ^^^ A more succinct expression for $(OBJECT_FILES), using
#     http://www.gnu.org/software/make/manual/make.html#Substitution-Refs

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BIN)
	rm -r -f $(OBJ)
	@# ^^^ I don't recommend suppressing the echoing of the command using @

# http://www.gnu.org/software/make/manual/make.html#Phony-Targets
#.PHONY: build clean
.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES) $(CPP_OBJECT_FILES)
	@mkdir -p $(BIN)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#Automatic-Variables
	@echo "Build successful!"

# http://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJECT_FILES): $(OBJ)/%.o: %.c libs 
	@echo Compiling $<
	@# ^^^ Your terminology is weird: you "compile a .cpp file" to create a .o file.
	@mkdir -p $(@D)
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	@$(CC) $(CFLAGS) -o $@ $<
	@# ^^^ Use $(CFLAGS), not $(LDFLAGS), when compiling.

# http://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(CPP_OBJECT_FILES): $(OBJ)/%.o: %.cpp libs 
	@echo Compiling $<
	@# ^^^ Your terminology is weird: you "compile a .cpp file" to create a .o file.
	@mkdir -p $(@D)
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	@$(CC) $(CFLAGS) -o $@ $<
	@# ^^^ Use $(CFLAGS), not $(LDFLAGS), when compiling.

.PHONY:	libs
libs:
	$(MAKE) -C ../../linked_list
