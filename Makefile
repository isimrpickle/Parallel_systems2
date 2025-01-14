CC = mpicc
CFLAGS = -g -Wall

#for the serial version of exercise2
CC_SERIAL = gcc

#defining the tagets
EXERCISE1_TARGET = modules/Game_of_Life
EXERCISE2_TARGET = modules/exercise2
EXERCISES_TARGET = modules/Serial_Exercise2

EXERCISE1_SRCS = modules/Game_of_Life.c  modules/my_rand.c
EXERCISE2_SRCS = modules/exercise2.c  modules/my_rand.c
EXERCISES_SRCS = modules/Serial_Exercise2.c


EXERCISE1_DIR = header_files

all: $(EXERCISE1_TARGET) $(EXERCISE2_TARGET) $(EXERCISES_TARGET)


$(EXERCISE1_TARGET): $(EXERCISE1_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE1_TARGET) $(EXERCISE1_SRCS)

$(EXERCISE2_TARGET): $(EXERCISE2_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE2_TARGET) $(EXERCISE2_SRCS)

$(EXERCISES_TARGET): $(EXERCISES_SRCS)
	$(CC_SERIAL) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISES_TARGET) $(EXERCISES_SRCS)




#clean build files
clean:
	rm -f $(EXERCISE1_TARGET) $(EXERCISE2_TARGET) $(EXERCISES_TARGET)