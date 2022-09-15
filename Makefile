CC = g++
OBJ_FLAGS = -c -O3
FLAGS = -O3 -o
NAME = lfu

SOURCE_PATH = "./source"

all: $(NAME) clean

$(NAME): main.o
	$(CC) *.o $(FLAGS) $(NAME)

main.o:
	$(CC) $(OBJ_FLAGS) $(SOURCE_PATH)/main.cpp

clean:
	rm *.o