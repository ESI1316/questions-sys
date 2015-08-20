CC=gcc
CFLAGS= -std=c99 -pedantic-errors
LFLAGS=
NOLINK= -c
ALL=as_trefle fork_boucle ls_wc process prod test client serveur

all : $(ALL)
as_trefle : as_trefle.o
	$(CC) $(LFLAGS) $^ -o $@
fork_boucle : fork_boucle.o
	$(CC) $(LFLAGS) $^ -o $@ 
ls_wc : ls_wc.o
	$(CC) $(LFLAGS) $^ -o $@ 
process : process.o
	$(CC) $(LFLAGS) $^ -o $@ 
prod : prod.o
	$(CC) $(LFLAGS) $^ -o $@ 
test : test.o
	$(CC) $(LFLAGS) $^ -o $@ 
client : client.o
	$(CC) $(LFLAGS) $^ -o $@ 
serveur : serveur.o
	$(CC) $(LFLAGS) $^ -o $@ 

%.o : %.c 
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

clean :
	@rm -rf *.o
	@rm -rf $(ALL)
