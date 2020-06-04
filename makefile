
OBJS = hw8.o 
arg = cs240.csv

CC = gcc 
FLAGS = -Wall -g

clean : all
	rm -f $(OBJS) *.a 

all : driver 
	./driver $(arg)


driver : driver.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ -lm

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<
