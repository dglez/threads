CC = gcc
FLAGS = -Wall -w
EXE = threads
OBJS = main.o 
SOURCE = main.c 

$(EXE):	$(OBJS)
		$(CC) $(FLAGS) $(SOURCE) -o $(EXE) $(LIBS)

.PHONY:	clean
clean:
	rm *.o