CC=gcc
CFLAGS= -std=c99 -pedantic-errors
LFLAGS=
NOLINK= -c
ALL=as_trefle PRc ls_wc process prod test client serveur shell_ls PRa PRb PRc PRd

all : Demo $(ALL)
	@clear

PRa : PRa.o
	$(CC) $(LFLAGS) $^ -o $@
PRb : PRb.o
	$(CC) $(LFLAGS) $^ -o $@
PRc : PRc.o
	$(CC) $(LFLAGS) $^ -o $@ 
PRd : PRd.o
	$(CC) $(LFLAGS) $^ -o $@ 
as_trefle : as_trefle.o
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
shell_ls : shell_ls.o
	$(CC) $(LFLAGS) $^ -o $@ 

%.o : %.c 
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

clean :
	@rm -rf *.o
	@rm -rf $(ALL)
