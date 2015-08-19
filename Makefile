CC=gcc
CFLAGS= -std=c99 -pedantic-errors
NOLINK= -c
ALL=as_trefle fork_boucle ls_wc process prod test

all : $(ALL)

as_trefle : as_trefle.o
	$(CC) $(CFLAGS) $^ -o $@

as_trefle.o : as_trefle.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

fork_boucle : fork_boucle.o
	$(CC) $(CFLAGS) $^ -o $@ 

fork_boucle.o : fork_boucle.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@ 

ls_wc : ls_wc.o
	$(CC) $(CFLAGS) $^ -o $@ 

ls_wc.o : ls_wc.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

process : process.o
	$(CC) $(CFLAGS) $^ -o $@ 

process.o : process.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

prod : prod.o
	$(CC) $(CFLAGS) $^ -o $@ 

prod.o : prod.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

test : test.o
	$(CC) $(CFLAGS) $^ -o $@ 

test.o : test.c
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

clean :
	rm -rf *.o
	rm -rf $(ALL)
