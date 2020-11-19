# C Compiler
CC = g++ 
CFLAGS = -fPIC -Wall -Wextra -O2 -g  -c -fpermissive

INC = -I ./inc

# Linking flags
LDFLAGS = 

RM = rm -f  # rm command

# Target lib
OUT_FILE_NAME = liblinked_list.a
OBJ_DIR=./obj
OUT_DIR=./lib

# Enumerating of every *.cpp as *.o and using that as dependency.
# filter list of .c files in a directory.
# FILES =dump_l.c \
#	kter.c \
#
# $(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard $(FILES)))


# Enumerating of every *.cpp as *.o and using that as dependency
SRC = src
SOURCE_FILES = $(wildcard $(SRC)**/*.cpp)
C_SOURCE_FILES = $(wildcard $(SRC)**/*.c)
#$(OUT_FILE_NAME): $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(wildcard *.cpp))
#$(OUT_FILE_NAME): $(patsubst $(SRC)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCE_FILES)) $(patsubst $(SRC)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCE_FILES))
$(OUT_FILE_NAME): $(patsubst $(SRC)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCE_FILES)) $(patsubst $(SRC)/%.c,$(C_OBJ_DIR)/%.o,$(C_SOURCE_FILES))
	ar -r -o $(OUT_DIR)/$@ $^
	@echo [  $(OUT_FILE_NAME)  ] created successfully! 



#Compiling every *.cpp to *.o
$(OBJ_DIR)/%.o: $(SRC)/%.cpp dirmake
	@echo Compiling: $<
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

#Compiling every *.c to *.o
$(C_OBJ_DIR)/%.o: $(SRC)/%.c dirmake
	@echo Compiling: $<
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OUT_DIR)/*.a $(OBJ_DIR)/*.o $(OUT_DIR)/$(OUT_FILE_NAME) Makefile.bak

rebuild: clean build
