CC = mpicc
CFLAGS = -g -Wall

#defining the tagets
EXERCISE1_TARGET = modules/Game_of_Life
EXERCISE2_TARGET = modules/exercise2

EXERCISE1_SRCS = modules/Game_of_Life.c  modules/my_rand.c
EXERCISE2_SRCS = modules/exercise2.c  modules/my_rand.c

EXERCISE1_DIR = header_files

all: $(EXERCISE1_TARGET) $(EXERCISE2_TARGET)


$(EXERCISE1_TARGET): $(EXERCISE1_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE1_TARGET) $(EXERCISE1_SRCS)

$(EXERCISE2_TARGET): $(EXERCISE2_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE2_TARGET) $(EXERCISE2_SRCS)




#clean build files
clean:
	rm -f $(EXERCISE1_TARGET) $(EXERCISE2_TARGET)