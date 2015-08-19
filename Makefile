CC=gcc
CFLAGS= -std=c99 -pedantic-errors
NOLINK= -c
ALL=as_trefle fork_boucle ls_wc process prod test

all : $(ALL)

as_trefle : as_trefle.o
	$(CC) $(CFLAGS) as_trefle.o -o as_trefle

as_trefle.o : as_trefle.c
	$(CC) $(CFLAGS) $(NOLINK) as_trefle.c -o as_trefle.o

fork_boucle : fork_boucle.o
	$(CC) $(CFLAGS) fork_boucle.o -o fork_boucle 

fork_boucle.o : fork_boucle.c
	$(CC) $(CFLAGS) $(NOLINK) fork_boucle.c -o fork_boucle.o

ls_wc : ls_wc.o
	$(CC) $(CFLAGS) ls_wc.o -o ls_wc

ls_wc.o : ls_wc.c
	$(CC) $(CFLAGS) $(NOLINK) ls_wc.c -o ls_wc.o

process : process.o
	$(CC) $(CFLAGS) process.o -o process 

process.o : process.c
	$(CC) $(CFLAGS) $(NOLINK) process.c -o process.o

prod : prod.o
	$(CC) $(CFLAGS) prod.o -o prod

prod.o : prod.c
	$(CC) $(CFLAGS) $(NOLINK) prod.c -o prod.o

test : test.o
	$(CC) $(CFLAGS) test.o -o test

test.o : test.c
	$(CC) $(CFLAGS) $(NOLINK) test.c -o test.o

clean :
	rm -rf *.o
	rm -rf $(ALL)
