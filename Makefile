CC = gcc
CFLAGS = -g
TARGET1 = Master
TARGET2 = Worker
OBJS1 = main.o
OBJS2 = worker.o

all: $(TARGET1) $(TARGET2)

Master: $(OBJS1)
	$(CC) $(CFLAGS) -o Master main.o

Worker: $(OBJS2)
	$(CC) $(FLAGS) -o Worker worker.o

clean:
	/bin/rm -f *.o $(TARGET)
	/bin/rm -f Master $(TARGET)
	/bin/rm -f Worker $(TARGET)
